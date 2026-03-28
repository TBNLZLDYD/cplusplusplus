import * as vscode from 'vscode';

export interface CompileError {
    line: number;
    column: number;
    message: string;
    severity: 'error' | 'warning';
}

export class OutputParser {
    static parse(output: string): CompileError[] {
        const errors: CompileError[] = [];
        const lines = output.split('\n');

        for (const line of lines) {
            const error = this.parseLine(line);
            if (error) {
                errors.push(error);
            }
        }

        return errors;
    }

    private static parseLine(line: string): CompileError | null {
        // Match Clang error format: file:line:column: error: message
        const match = line.match(/(.+?):(\d+):(\d+):\s*(error|warning):\s*(.+)/);
        if (match) {
            return {
                line: parseInt(match[2]),
                column: parseInt(match[3]),
                message: match[5],
                severity: match[4] as 'error' | 'warning'
            };
        }

        return null;
    }

    static createDiagnostics(errors: CompileError[]): vscode.Diagnostic[] {
        const diagnostics: vscode.Diagnostic[] = [];

        for (const error of errors) {
            const position = new vscode.Position(error.line - 1, error.column - 1);
            const range = new vscode.Range(position, position);
            const severity = error.severity === 'error' ? 
                vscode.DiagnosticSeverity.Error : 
                vscode.DiagnosticSeverity.Warning;

            const diagnostic = new vscode.Diagnostic(
                range,
                error.message,
                severity
            );

            diagnostic.source = 'C+++';
            diagnostics.push(diagnostic);
        }

        return diagnostics;
    }
}