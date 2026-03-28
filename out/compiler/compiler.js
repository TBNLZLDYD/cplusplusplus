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
exports.Compiler = void 0;
const child_process = __importStar(require("child_process"));
const parser_1 = require("./parser");
class Compiler {
    constructor(config) {
        this.config = config;
    }
    compile(filePath) {
        return __awaiter(this, void 0, void 0, function* () {
            const args = this.buildCompileArgs(filePath);
            return new Promise((resolve, reject) => {
                child_process.execFile(this.config.clangPath, args, { timeout: 30000 }, (error, stdout, stderr) => {
                    try {
                        const result = {
                            success: !error,
                            errors: parser_1.OutputParser.parse(stderr),
                            output: stdout + stderr
                        };
                        resolve(result);
                    }
                    catch (err) {
                        reject(err);
                    }
                });
            });
        });
    }
    buildCompileArgs(filePath) {
        const args = [];
        // Add C+++ plugin
        if (this.config.cplusplusplusPluginPath) {
            args.push(`-Xclang`);
            args.push(`-load`);
            args.push(`-Xclang`);
            args.push(this.config.cplusplusplusPluginPath);
        }
        // Add include paths
        for (const includePath of this.config.includePaths) {
            args.push(`-I${includePath}`);
        }
        // Add compiler flags
        args.push(...this.config.compilerFlags);
        // Add input file
        args.push(filePath);
        return args;
    }
}
exports.Compiler = Compiler;
//# sourceMappingURL=compiler.js.map