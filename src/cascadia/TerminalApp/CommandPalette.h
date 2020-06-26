// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once

#include "CommandPalette.g.h"
#include "../../cascadia/inc/cppwinrt_utils.h"

namespace winrt::TerminalApp::implementation
{
    struct CommandPalette : CommandPaletteT<CommandPalette>
    {
        CommandPalette();

        Windows::Foundation::Collections::IObservableVector<TerminalApp::Command> FilteredActions();
        void SetActions(Windows::Foundation::Collections::IVector<TerminalApp::Command> const& actions);
        void ToggleVisibility();
        void SetDispatch(const winrt::TerminalApp::ShortcutActionDispatch& dispatch);
        void SetKeyBindings(const winrt::Microsoft::Terminal::Settings::IKeyBindings& bindings);

        TYPED_EVENT(Closed, TerminalApp::CommandPalette, winrt::Windows::UI::Xaml::RoutedEventArgs);

    private:
        friend struct CommandPaletteT<CommandPalette>; // for Xaml to bind events

        Windows::Foundation::Collections::IObservableVector<TerminalApp::Command> _filteredActions{ nullptr };
        Windows::Foundation::Collections::IVector<TerminalApp::Command> _allActions{ nullptr };
        winrt::TerminalApp::ShortcutActionDispatch _dispatch;
        winrt::Microsoft::Terminal::Settings::IKeyBindings _keyBindings;

        void _filterTextChanged(Windows::Foundation::IInspectable const& sender,
                                Windows::UI::Xaml::RoutedEventArgs const& args);
        void _keyDownHandler(Windows::Foundation::IInspectable const& sender,
                             Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e);

        void _rootPointerPressed(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void _backdropPointerPressed(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);

        void _listItemClicked(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::ItemClickEventArgs const& e);

        void _selectNextItem(const bool moveDown);

        void _updateFilteredActions();
        static int _getWeight(const winrt::hstring& searchText, const winrt::hstring& name);
        void _close();
    };
}

namespace winrt::TerminalApp::factory_implementation
{
    BASIC_FACTORY(CommandPalette);
}
