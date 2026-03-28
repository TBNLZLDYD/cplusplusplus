import * as child_process from 'child_process';
import { OutputParser } from './parser';

export interface CompileConfig {
    clangPath: string;
    cplusplusplusPluginPath: string;
    includePaths: string[];
    compilerFlags: string[];
}

export interface CompileError {
    line: number;
    column: number;
    message: string;
    severity: 'error' | 'warning';
}

export interface CompileResult {
    success: boolean;
    errors: CompileError[];
    output: string;
}

export class Compiler {
    private config: CompileConfig;

    constructor(config: CompileConfig) {
        this.config = config;
    }

    async compile(filePath: string): Promise<CompileResult> {
        const args = this.buildCompileArgs(filePath);

        return new Promise((resolve, reject) => {
            child_process.execFile(this.config.clangPath, args, { timeout: 30000 }, (error, stdout, stderr) => {
                try {
                    const result: CompileResult = {
                        success: !error,
                        errors: OutputParser.parse(stderr),
                        output: stdout + stderr
                    };
                    resolve(result);
                } catch (err) {
                    reject(err);
                }
            });
        });
    }

    private buildCompileArgs(filePath: string): string[] {
        const args: string[] = [];

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