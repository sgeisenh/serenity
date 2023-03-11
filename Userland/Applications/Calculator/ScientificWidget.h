/*
 * Copyright (c) 2019-2020, Sergey Bugaev <bugaevc@serenityos.org>
 * Copyright (c) 2021, Glenford Williams <gw_dev@outlook.com>
 * Copyright (c) 2022, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "WidgetInterface.h"
#include "Calculator.h"
#include "Keypad.h"
#include <AK/Vector.h>
#include <LibCrypto/BigFraction/BigFraction.h>
#include <LibGUI/Action.h>
#include <LibGUI/Widget.h>

class ScientificWidget final : public WidgetInterface {
    C_OBJECT(ScientificWidget)
public:
    virtual ~ScientificWidget() override = default;
    DeprecatedString get_entry() override;
    void set_entry(Crypto::BigFraction) override;
    void set_typed_entry(Crypto::BigFraction) override;

    void shrink(unsigned) override;
    unsigned rounding_length() const override;
    void set_rounding_length(unsigned) override;

    void set_rounding_custom(GUI::Action& action, StringView) override;

    CalcState get_state() override;

private:
    ScientificWidget();
    ScientificWidget(CalcState state);

    void add_operation_button(GUI::Button&, Calculator::Operation);
    void add_digit_button(GUI::Button&, int digit);

    void perform_operation(Calculator::Operation operation);
    void update_display();

    virtual void keydown_event(GUI::KeyEvent&) override;

    Calculator m_calculator;
    Keypad m_keypad;

    RefPtr<GUI::TextBox> m_entry;
    RefPtr<GUI::Label> m_label;

    RefPtr<GUI::Button> m_digit_button[10];
    RefPtr<GUI::Button> m_mem_add_button;
    RefPtr<GUI::Button> m_mem_save_button;
    RefPtr<GUI::Button> m_mem_recall_button;
    RefPtr<GUI::Button> m_mem_clear_button;
    RefPtr<GUI::Button> m_clear_button;
    RefPtr<GUI::Button> m_clear_error_button;
    RefPtr<GUI::Button> m_backspace_button;
    RefPtr<GUI::Button> m_decimal_point_button;
    RefPtr<GUI::Button> m_sign_button;
    RefPtr<GUI::Button> m_add_button;
    RefPtr<GUI::Button> m_subtract_button;
    RefPtr<GUI::Button> m_multiply_button;
    RefPtr<GUI::Button> m_divide_button;
    RefPtr<GUI::Button> m_sqrt_button;
    RefPtr<GUI::Button> m_inverse_button;
    RefPtr<GUI::Button> m_percent_button;
    RefPtr<GUI::Button> m_equals_button;
    RefPtr<GUI::Button> m_sin_button;
    RefPtr<GUI::Button> m_cos_button;
    RefPtr<GUI::Button> m_tan_button;

    StringView m_format;
    RefPtr<GUI::Action> m_rounding_custom;
};
