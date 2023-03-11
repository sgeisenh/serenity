/*
 * Copyright (c) 2020, Matthew Olsson <mattco@serenityos.org>
 * Copyright (c) 2022-2023, Linus Groh <linusg@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibJS/Heap/Heap.h>
#include <LibJS/Runtime/Symbol.h>
#include <LibJS/Runtime/VM.h>

namespace JS {

Symbol::Symbol(Optional<String> description, bool is_global)
    : m_description(move(description))
    , m_is_global(is_global)
{
}

NonnullGCPtr<Symbol> Symbol::create(VM& vm, Optional<String> description, bool is_global)
{
    return vm.heap().allocate_without_realm<Symbol>(move(description), is_global);
}

// 20.4.3.3.1 SymbolDescriptiveString ( sym ), https://tc39.es/ecma262/#sec-symboldescriptivestring
ErrorOr<String> Symbol::descriptive_string() const
{
    // 1. Let desc be sym's [[Description]] value.
    // 2. If desc is undefined, set desc to the empty String.
    // 3. Assert: desc is a String.
    auto description = m_description.value_or(String {});

    // 4. Return the string-concatenation of "Symbol(", desc, and ")".
    return String::formatted("Symbol({})", description);
}

}
