#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class CRONICS_API SSSDialogoWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SSSDialogoWidget) {}
        SLATE_ARGUMENT(FText, DialogoTexto)
    SLATE_END_ARGS()

    /** Constructs this widget with InArgs */
    void Construct(const FArguments& InArgs);

    /** Function to update the text */
    void ActualizarTexto(FText NuevoTexto);

private:
    TSharedPtr<STextBlock> TextoBloque;
};