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
}
