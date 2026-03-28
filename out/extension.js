"use strict";
var __createBinding = (this && this.__createBinding) || (Object.create ? (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    var desc = Object.getOwnPropertyDescriptor(m, k);
    if (!desc || ("get" in desc ? !m.__esModule : desc.writable || desc.configurable)) {
      desc = { enumerable: true, get: function() { return m[k]; } };
    }
    Object.defineProperty(o, k2, desc);
}) : (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    o[k2] = m[k];
}));
var __setModuleDefault = (this && this.__setModuleDefault) || (Object.create ? (function(o, v) {
    Object.defineProperty(o, "default", { enumerable: true, value: v });
}) : function(o, v) {
    o["default"] = v;
});
var __importStar = (this && this.__importStar) || function (mod) {
    if (mod && mod.__esModule) return mod;
    var result = {};
    if (mod != null) for (var k in mod) if (k !== "default" && Object.prototype.hasOwnProperty.call(mod, k)) __createBinding(result, mod, k);
    __setModuleDefault(result, mod);
    return result;
};
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.deactivate = exports.activate = void 0;
const vscode = __importStar(require("vscode"));
const config_1 = require("./utils/config");
const status_1 = require("./utils/status");
const compiler_1 = require("./compiler/compiler");
const parser_1 = require("./compiler/parser");
function activate(context) {
    console.log('C+++ VSCode extension activated');
    // Create diagnostic collection
    const diagnosticCollection = vscode.languages.createDiagnosticCollection('cplusplusplus');
    context.subscriptions.push(diagnosticCollection);
    // Create status manager
    const statusManager = new status_1.StatusManager();
    context.subscriptions.push(statusManager);
    // Activate status manager
    statusManager.activate();
    // Register commands
    const compileCommand = vscode.commands.registerCommand('cplusplusplus.compile', () => __awaiter(this, void 0, void 0, function* () {
        const editor = vscode.window.activeTextEditor;
        if (!editor) {
            vscode.window.showErrorMessage('No active editor');
            return;
        }
        const document = editor.document;
        const filePath = document.uri.fsPath;
        const config = config_1.ConfigManager.getConfig();
        if (!config_1.ConfigManager.validateConfig(config)) {
            return;
        }
        const compiler = new compiler_1.Compiler({
            clangPath: config.cplusplusplus.clangPath,
            cplusplusplusPluginPath: config.cplusplusplus.pluginPath,
            includePaths: [],
            compilerFlags: []
        });
        try {
            vscode.window.showInformationMessage('C+++: Compiling...');
            statusManager.setCompilationStatus('running');
            const result = yield compiler.compile(filePath);
            if (result.success) {
                vscode.window.showInformationMessage('C+++: Compilation successful');
                statusManager.setCompilationStatus('success');
                statusManager.setErrorCount(0);
                diagnosticCollection.clear();
            }
            else {
                vscode.window.showErrorMessage(`C+++: Compilation failed with ${result.errors.length} errors`);
                statusManager.setCompilationStatus('failed');
                statusManager.setErrorCount(result.errors.length);
                // Create diagnostics
                const diagnostics = parser_1.OutputParser.createDiagnostics(result.errors);
                diagnosticCollection.set(document.uri, diagnostics);
            }
        }
        catch (error) {
            vscode.window.showErrorMessage(`C+++: Compilation error: ${error}`);
            statusManager.setCompilationStatus('failed');
            statusManager.setErrorCount(1);
        }
    }));
    // Add to context subscriptions
    context.subscriptions.push(compileCommand);
    // Initialize configuration
    const config = config_1.ConfigManager.getConfig();
    console.log('C+++ configuration loaded:', config);
    // Register semantic tokens provider for syntax highlighting
    if (config.cplusplusplus.enableSyntaxHighlighting) {
        const semanticTokensLegend = new vscode.SemanticTokensLegend(['keyword', 'operator'], ['declaration']);
        const semanticTokensProvider = vscode.languages.registerDocumentSemanticTokensProvider('cpp', {
            provideDocumentSemanticTokens(document, _token) {
                const tokens = [];
                // C+++ keywords
                const keywords = ['let', 'var', 'defer', 'match', 'interface'];
                // C+++ operators
                const operators = ['|>', '??'];
                const text = document.getText();
                let offset = 0;
                // Simple tokenization with proper string and comment handling
                const lines = text.split('\n');
                let inBlockComment = false;
                for (let lineIndex = 0; lineIndex < lines.length; lineIndex++) {
                    const line = lines[lineIndex];
                    let currentOffset = 0;
                    while (currentOffset < line.length) {
                        // Check for block comment start/end
                        if (inBlockComment) {
                            const endCommentIndex = line.indexOf('*/', currentOffset);
                            if (endCommentIndex !== -1) {
                                currentOffset = endCommentIndex + 2;
                                inBlockComment = false;
                            }
                            else {
                                // Remainder of line is comment
                                break;
                            }
                        }
                        else {
                            // Check for line comment
                            const lineCommentIndex = line.indexOf('//', currentOffset);
                            if (lineCommentIndex !== -1) {
                                // Process up to comment
                                processLineSegment(line.substring(currentOffset, lineCommentIndex), offset + currentOffset);
                                break; // Skip rest of line
                            }
                            // Check for block comment start
                            const blockCommentIndex = line.indexOf('/*', currentOffset);
                            if (blockCommentIndex !== -1) {
                                // Process up to comment start
                                processLineSegment(line.substring(currentOffset, blockCommentIndex), offset + currentOffset);
                                currentOffset = blockCommentIndex;
                                inBlockComment = true;
                            }
                            else {
                                // Process entire line
                                processLineSegment(line.substring(currentOffset), offset + currentOffset);
                                break;
                            }
                        }
                    }
                    offset += line.length + 1; // +1 for newline
                }
                function processLineSegment(segment, segmentOffset) {
                    // Track string state
                    let inDoubleQuote = false;
                    let inSingleQuote = false;
                    let escapeNext = false;
                    for (let i = 0; i < segment.length; i++) {
                        const char = segment[i];
                        if (escapeNext) {
                            escapeNext = false;
                            continue;
                        }
                        if (char === '\\') {
                            escapeNext = true;
                            continue;
                        }
                        if (char === '"' && !inSingleQuote) {
                            inDoubleQuote = !inDoubleQuote;
                            continue;
                        }
                        if (char === "'" && !inDoubleQuote) {
                            inSingleQuote = !inSingleQuote;
                            continue;
                        }
                        // Only process if not inside string
                        if (!inDoubleQuote && !inSingleQuote) {
                            // Check for keywords
                            for (const keyword of keywords) {
                                if (i + keyword.length <= segment.length) {
                                    const potentialKeyword = segment.substring(i, i + keyword.length);
                                    const isKeyword = potentialKeyword === keyword;
                                    const isWordBoundaryBefore = i === 0 || !/[a-zA-Z0-9_]/.test(segment[i - 1]);
                                    const isWordBoundaryAfter = i + keyword.length === segment.length || !/[a-zA-Z0-9_]/.test(segment[i + keyword.length]);
                                    if (isKeyword && isWordBoundaryBefore && isWordBoundaryAfter) {
                                        const start = document.positionAt(segmentOffset + i);
                                        tokens.push(start.line, start.character, keyword.length, 0, 0); // keyword, no modifiers
                                        i += keyword.length - 1; // Skip ahead
                                        break;
                                    }
                                }
                            }
                            // Check for operators
                            for (const op of operators) {
                                if (i + op.length <= segment.length && segment.substring(i, i + op.length) === op) {
                                    const start = document.positionAt(segmentOffset + i);
                                    tokens.push(start.line, start.character, op.length, 1, 0); // operator, no modifiers
                                    i += op.length - 1; // Skip ahead
                                    break;
                                }
                            }
                        }
                    }
                }
                return {
                    data: new Uint32Array(tokens),
                    resultId: undefined
                };
            }
        }, semanticTokensLegend);
        context.subscriptions.push(semanticTokensProvider);
    }
    // Register hover provider if enabled
    if (config.cplusplusplus.enableHover) {
        const hoverProvider = vscode.languages.registerHoverProvider('cpp', {
            provideHover(_document, _position, _token) {
                return {
                    contents: [
                        new vscode.MarkdownString('# C+++ Language Feature'),
                        new vscode.MarkdownString('This is a C+++ language feature.\n\nFeatures include:\n- `let`/`var` for type inference\n- `defer` for resource management\n- `|>` pipe operator\n- `match` statement for pattern matching\n- `interface` for pure virtual classes')
                    ]
                };
            }
        });
        context.subscriptions.push(hoverProvider);
    }
    // Register code action provider if enabled
    if (config.cplusplusplus.enableQuickFix) {
        const codeActionProvider = vscode.languages.registerCodeActionsProvider('cpp', {
            provideCodeActions(_document, _range, _context, _token) {
                return [];
            }
        });
        context.subscriptions.push(codeActionProvider);
    }
}
exports.activate = activate;
function deactivate() {
    console.log('C+++ VSCode extension deactivated');
    // Status manager will be automatically disposed by context subscriptions
}
exports.deactivate = deactivate;
//# sourceMappingURL=extension.js.map