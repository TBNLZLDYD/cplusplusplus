import * as vscode from 'vscode';

export interface PluginState {
    activated: boolean;
    cplusplusplusPluginLoaded: boolean;
    compilationStatus: 'idle' | 'running' | 'success' | 'failed';
    errorCount: number;
}

export class StatusManager {
    private statusBarItem: vscode.StatusBarItem;
    private state: PluginState;

    constructor() {
        this.statusBarItem = vscode.window.createStatusBarItem(vscode.StatusBarAlignment.Left);
        this.state = {
            activated: false,
            cplusplusplusPluginLoaded: false,
            compilationStatus: 'idle',
            errorCount: 0
        };
        this.updateStatus();
    }

    activate() {
        this.state.activated = true;
        this.updateStatus();
    }

    deactivate() {
        this.state.activated = false;
        this.updateStatus();
        this.statusBarItem.dispose();
    }

    setCPlusPlusPlusPluginLoaded(loaded: boolean) {
        this.state.cplusplusplusPluginLoaded = loaded;
        this.updateStatus();
    }

    setCompilationStatus(status: 'idle' | 'running' | 'success' | 'failed') {
        this.state.compilationStatus = status;
        this.updateStatus();
    }

    setErrorCount(count: number) {
        this.state.errorCount = count;
        this.updateStatus();
    }

    private updateStatus() {
        let text = 'C+++';

        if (!this.state.activated) {
            text += ' (Inactive)';
        } else {
            if (this.state.cplusplusplusPluginLoaded) {
                text += ' (Plugin Loaded)';
            } else {
                text += ' (Plugin Not Loaded)';
            }

            switch (this.state.compilationStatus) {
                case 'running':
                    text += ' [Compiling...]';
                    break;
                case 'success':
                    text += ' [Success]';
                    break;
                case 'failed':
                    text += ` [Failed: ${this.state.errorCount} errors]`;
                    break;
            }
        }

        this.statusBarItem.text = text;
        this.statusBarItem.show();
    }

    getState(): PluginState {
        return { ...this.state };
    }

    dispose() {
        this.statusBarItem.dispose();
    }
}