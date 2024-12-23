package com.pine.comp;

import com.pine.impl.AbstractView;
import com.pine.comp.impl.*;
import com.pine.engine.inspection.FieldDTO;
import com.pine.engine.inspection.Inspectable;
import imgui.ImGui;

import java.util.HashMap;
import java.util.Map;
import java.util.function.BiConsumer;

public class FormPanel extends AbstractView {
    private final BiConsumer<FieldDTO, Object> changeHandler;
    private Inspectable inspectable;

    public FormPanel(BiConsumer<FieldDTO, Object> changeHandler) {
        this.changeHandler = changeHandler;
    }

    public void setInspectable(Inspectable data) {
        if (this.inspectable == data) {
            return;
        }
        this.inspectable = data;
        children.clear();

        if (data == null) {
            return;
        }
        Map<String, AccordionPanel> groups = new HashMap<>();
        for (FieldDTO field : data.getFieldsAnnotated()) {
            if (!groups.containsKey(field.getGroup())) {
                groups.put(field.getGroup(), appendChild(new AccordionPanel()));
            }

            AccordionPanel group = groups.get(field.getGroup());
            group.title = field.getGroup();
            switch (field.getType()) {
                case STRING:
                    group.appendChild(new StringField(field, changeHandler));
                    break;
                case INT:
                    group.appendChild(new IntField(field, changeHandler));
                    break;
                case FLOAT:
                    group.appendChild(new FloatField(field, changeHandler));
                    break;
                case BOOLEAN:
                    group.appendChild(new BooleanField(field, changeHandler));
                    break;
                case VECTOR2:
                    group.appendChild(new Vector2Field(field, changeHandler));
                    break;
                case VECTOR3:
                    group.appendChild(new Vector3Field(field, changeHandler));
                    break;
                case VECTOR4:
                    group.appendChild(new Vector4Field(field, changeHandler));
                    break;
                case QUATERNION:
                    group.appendChild(new QuaternionField(field, changeHandler));
                    break;
                case COLOR:
                    group.appendChild(new ColorField(field, changeHandler));
                    break;
                case OPTIONS:
                    group.appendChild(new OptionsField(field, changeHandler));
                    break;
            }
        }
    }

    public Inspectable getInspectable() {
        return inspectable;
    }

    @Override
    public void render() {
        if (inspectable != null) {
            ImGui.text(inspectable.getIcon() + inspectable.getTitle());
            ImGui.separator();
            super.render();
        }
    }
}
