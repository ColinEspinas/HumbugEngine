/*
 * Copyright (C) 2017 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

WebInspector.SettingEditor = class SettingEditor extends WebInspector.Object
{
    constructor(type, label, options)
    {
        super();

        this._type = type;
        this._label = label;
        this._value = null;

        this._editorElement = this._createEditorElement(options);
        console.assert(this._editorElement);

        this._element = document.createElement("div");
        this._element.classList.add("editor");
        this._element.append(this._editorElement);

        if (this._label) {
            this._editorElement.id = "setting-editor-" + WebInspector.SettingEditor._nextEditorIdentifier++;
            let labelElement = document.createElement("label");
            labelElement.setAttribute("for", this._editorElement.id);
            labelElement.textContent = label;

            this._element.append(labelElement);
        }
    }

    static createForSetting(setting, label, options)
    {
        let type;
        if (typeof setting.value === "boolean")
            type = WebInspector.SettingEditor.Type.Checkbox;
        else if (typeof setting.value === "number")
            type = WebInspector.SettingEditor.Type.Numeric;

        console.assert(type, "Cannot deduce editor type from setting value type.", setting);
        if (!type)
            return null;

        let editor = new WebInspector.SettingEditor(type, label, options);
        editor.value = setting.value;
        editor.addEventListener(WebInspector.SettingEditor.Event.ValueDidChange, () => { setting.value = editor.value; });

        return editor;
    }

    // Public

    get element() { return this._element; }
    get type() { return this._type; }
    get label() { return this._label; }

    get value()
    {
        return this._value;
    }

    set value(value)
    {
        if (this._value === value)
            return;

        let oldValue = this._value;
        this._value = value;

        if (this._type == WebInspector.SettingEditor.Type.Checkbox)
            this._editorElement.checked = !!this._value;
        else
            this._editorElement.value = this._value;

        this.dispatchEventToListeners(WebInspector.SettingEditor.Event.ValueDidChange, {oldValue});
    }

    // Private

    _createEditorElement(options)
    {
        let editorElement;

        switch (this._type) {
        case WebInspector.SettingEditor.Type.Checkbox:
            editorElement = document.createElement("input");
            editorElement.type = "checkbox";
            editorElement.addEventListener("change", (event) => { this.value = event.target.checked; });
            break;

        case WebInspector.SettingEditor.Type.Numeric:
            editorElement = document.createElement("input");
            editorElement.type = "number";

            if (options.min !== undefined)
                editorElement.min = options.min;
            if (options.max !== undefined)
                editorElement.max = options.max;

            editorElement.addEventListener("change", (event) => {
                let currentValue = this._value;
                let newValue = parseInt(event.target.value);
                this.value = isNaN(newValue) ? currentValue : newValue;
            });
            break;

        case WebInspector.SettingEditor.Type.Select:
            editorElement = document.createElement("select");
            var keyValuePairs = [];

            console.assert(Array.isArray(options.values), "Expected values array for select editor.", options);

            if (Array.isArray(options.values[0]))
                keyValuePairs = options.values;
            else
                keyValuePairs = options.values.map((value) => [value, value]);

            for (let [key, value] of keyValuePairs) {
                let optionElement = editorElement.appendChild(document.createElement("option"));
                optionElement.value = key;
                optionElement.textContent = value;
            }

            editorElement.addEventListener("change", (event) => { this.value = event.target.value; });
            break;

        default:
            console.error("Unknown editor type: " + this._type);
        }

        return editorElement;
    }
};

WebInspector.SettingEditor._nextEditorIdentifier = 1;

WebInspector.SettingEditor.Type = {
    Checkbox: "setting-editor-type-checkbox",
    Numeric: "setting-editor-type-numeric",
    Select: "setting-editor-type-select",
};

WebInspector.SettingEditor.Event = {
    ValueDidChange: "value-did-change",
};
