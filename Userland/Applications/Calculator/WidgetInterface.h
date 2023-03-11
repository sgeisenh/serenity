/*
 * Copyright (c) 2019-2020, Sergey Bugaev <bugaevc@serenityos.org>
 * Copyright (c) 2021, Glenford Williams <gw_dev@outlook.com>
 * Copyright (c) 2022, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "Calculator.h"
#include "Keypad.h"
#include <AK/Vector.h>
#include <LibCrypto/BigFraction/BigFraction.h>
#include <LibGUI/Action.h>
#include <LibGUI/Widget.h>

struct CalcState {
    Calculator calculator;
    Keypad keypad;
    StringView format;
    RefPtr<GUI::Action> rounding_custom;
};

class WidgetInterface : public GUI::Widget {
public:
    virtual ~WidgetInterface() override = default;
    virtual DeprecatedString get_entry() = 0;
    virtual void set_entry(Crypto::BigFraction) = 0;
    virtual void set_typed_entry(Crypto::BigFraction) = 0;

    virtual void shrink(unsigned) = 0;
    virtual unsigned rounding_length() const = 0;
    virtual void set_rounding_length(unsigned) = 0;

    virtual void set_rounding_custom(GUI::Action& action, StringView) = 0;

    virtual CalcState get_state() = 0;
};
