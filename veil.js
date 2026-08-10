const shader = QStandardPaths.locate(QStandardPaths.GenericDataLocation, "veil/veil.glsl");

const effect = new QObject();

function init() {
    if (!effects.isOpenGLCompositing()) {
        print("Veil: OpenGL compositing not available");
        return;
    }

    effect.shader = effects.addFragmentShader(shader);

    if (!effect.shader) {
        print("Veil: Failed to load shader");
        return;
    }

    effects.paintScreen.connect(function(mask, region, data) {
        effects.setShader(effect.shader);
        effects.setUniform(effect.shader, "hue", 240.0);      // blue hue
        effects.setUniform(effect.shader, "intensity", 0.5);   // 50% blend
        effects.setUniform(effect.shader, "resolution",
            [effects.virtualScreenSize.width, effects.virtualScreenSize.height]);
    });
}

init();