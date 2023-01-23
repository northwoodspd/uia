#include "Stdafx.h"

extern "C"
{
    __declspec(dllexport) int ComboBox_GetItems(ElementInformationPtr element, ElementInformation** items, char* errorInfo, const int errorInfoLength)
    {
        try {
            int count = 0;

            ElementFrom(element)->As<ExpandCollapsePattern^>(ExpandCollapsePattern::Pattern)->Expand();

            if ("ComboLBox" == Element::Windows[0]->ClassName)
            {
                auto childElements = Element::Windows[0]->Children;
                *items = ElementInformation::From(childElements);
                count = childElements->Length;
            }
            else
            {
                StringHelper::CopyToUnmanagedString("Unable to find list control associated with combo box", errorInfo, errorInfoLength);
            }

            ElementFrom(element)->As<ExpandCollapsePattern^>(ExpandCollapsePattern::Pattern)->Collapse();

            return count;
        }
        catch (Exception^ e) {
            StringHelper::CopyToUnmanagedString(e, errorInfo, errorInfoLength);
            return 0;
        }
    }

    __declspec(dllexport) void ComboBox_SetItemByIndex(ElementInformationPtr element, const int itemIndex, char* errorInfo, const int errorInfoLength)
    {
        try {
            ElementFrom(element)->As<ExpandCollapsePattern^>(ExpandCollapsePattern::Pattern)->Expand();

            if ("ComboLBox" == Element::Windows[0]->ClassName)
            {
                auto childElements = Element::Windows[0]->Children;
                if (childElements->Length > itemIndex && itemIndex > -1)
                {
                    childElements[itemIndex]->As<SelectionItemPattern^>(SelectionItemPattern::Pattern)->Select();
                }
                else
                {
                    StringHelper::CopyToUnmanagedString("Specified index was not found in combo box list", errorInfo, errorInfoLength);
                }
            }
            else
            {
                StringHelper::CopyToUnmanagedString("Unable to find list control associated with combo box", errorInfo, errorInfoLength);
            }

            ElementFrom(element)->As<ExpandCollapsePattern^>(ExpandCollapsePattern::Pattern)->Collapse();
        }
        catch (Exception^ e) {
            StringHelper::CopyToUnmanagedString(e, errorInfo, errorInfoLength);
        }
    }

    __declspec(dllexport) void ComboBox_SetItemByValue(ElementInformationPtr element, const char* itemValue, char* errorInfo, const int errorInfoLength)
    {
        try {
            ElementFrom(element)->As<ExpandCollapsePattern^>(ExpandCollapsePattern::Pattern)->Expand();

            if ("ComboLBox" == Element::Windows[0]->ClassName)
            {
                auto childElements = Element::Windows[0]->Children;
                for each (auto item in childElements)
                {
                    if (strcmp(StringHelper::ToUnmanaged(item->Name), itemValue) == 0)
                    {
                        item->As<SelectionItemPattern^>(SelectionItemPattern::Pattern)->Select();
                    }
                }
            }
            else
            {
                StringHelper::CopyToUnmanagedString("Unable to find list control associated with combo box", errorInfo, errorInfoLength);
            }

            ElementFrom(element)->As<ExpandCollapsePattern^>(ExpandCollapsePattern::Pattern)->Collapse();
        }
        catch (Exception^ e) {
            StringHelper::CopyToUnmanagedString(e, errorInfo, errorInfoLength);
        }
    }
}
