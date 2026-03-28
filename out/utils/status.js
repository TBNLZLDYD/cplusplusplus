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
exports.StatusManager = void 0;
const vscode = __importStar(require("vscode"));
class StatusManager {
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
    setCPlusPlusPlusPluginLoaded(loaded) {
        this.state.cplusplusplusPluginLoaded = loaded;
        this.updateStatus();
    }
    setCompilationStatus(status) {
        this.state.compilationStatus = status;
        this.updateStatus();
    }
    setErrorCount(count) {
        this.state.errorCount = count;
        this.updateStatus();
    }
    updateStatus() {
        let text = 'C+++';
        if (!this.state.activated) {
            text += ' (Inactive)';
        }
        else {
            if (this.state.cplusplusplusPluginLoaded) {
                text += ' (Plugin Loaded)';
            }
            else {
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
    getState() {
        return Object.assign({}, this.state);
    }
    dispose() {
        this.statusBarItem.dispose();
    }
}
exports.StatusManager = StatusManager;
//# sourceMappingURL=status.js.map