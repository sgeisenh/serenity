/*
 * Copyright (c) 2021, Ali Mohammad Pur <mpfard@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "WebAssemblyMemoryConstructor.h"
#include <LibJS/Runtime/Object.h>
#include <LibJS/Runtime/VM.h>
#include <LibWeb/Forward.h>

namespace Web::Bindings {

class WebAssemblyMemoryPrototype final : public JS::Object {
    JS_OBJECT(WebAssemblyMemoryPrototype, JS::Object);

public:
    explicit WebAssemblyMemoryPrototype(JS::Realm& realm)
        : JS::Object(ConstructWithPrototypeTag::Tag, *realm.intrinsics().object_prototype())
    {
    }

    virtual JS::ThrowCompletionOr<void> initialize(JS::Realm&) override;

private:
    JS_DECLARE_NATIVE_FUNCTION(grow);
    JS_DECLARE_NATIVE_FUNCTION(buffer_getter);
};

}
