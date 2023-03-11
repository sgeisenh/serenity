serenity_component(
    Calculator
    RECOMMENDED
    TARGETS Calculator
)

compile_gml(CalculatorWindow.gml CalculatorGML.h calculator_gml)
compile_gml(ScientificWindow.gml ScientificGML.h scientific_gml)
set(SOURCES
    main.cpp
    Calculator.cpp
    CalculatorWidget.cpp
    RoundingDialog.cpp
    ScientificWidget.cpp
    Keypad.cpp
)

set(GENERATED_SOURCES
    CalculatorGML.h
    ScientificGML.h
)

serenity_app(Calculator ICON app-calculator)
target_link_libraries(Calculator PRIVATE LibCore LibCrypto LibGfx LibGUI LibMain)
