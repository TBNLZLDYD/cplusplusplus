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
Object.defineProperty(exports, "__esModule", { value: true });
exports.OutputParser = void 0;
const vscode = __importStar(require("vscode"));
class OutputParser {
    static parse(output) {
        const errors = [];
        const lines = output.split('\n');
        for (const line of lines) {
            const error = this.parseLine(line);
            if (error) {
                errors.push(error);
            }
        }
        return errors;
    }
    static parseLine(line) {
        // Match Clang error format: file:line:column: error: message
        const match = line.match(/(.+?):(\d+):(\d+):\s*(error|warning):\s*(.+)/);
        if (match) {
            return {
                line: parseInt(match[2]),
                column: parseInt(match[3]),
                message: match[5],
                severity: match[4]
            };
        }
        return null;
    }
    static createDiagnostics(errors) {
        const diagnostics = [];
        for (const error of errors) {
            const position = new vscode.Position(error.line - 1, error.column - 1);
            const range = new vscode.Range(position, position);
            const severity = error.severity === 'error' ?
                vscode.DiagnosticSeverity.Error :
                vscode.DiagnosticSeverity.Warning;
            const diagnostic = new vscode.Diagnostic(range, error.message, severity);
            diagnostic.source = 'C+++';
            diagnostics.push(diagnostic);
        }
        return diagnostics;
    }
}
exports.OutputParser = OutputParser;
//# sourceMappingURL=parser.js.map