#include "SSSDialogoWidget.h"
#include "SlateOptMacros.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBorder.h"  // Para el borde
#include "Widgets/Layout/SBox.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSSDialogoWidget::Construct(const FArguments& InArgs)
{
    FSlateFontInfo FontInfo = FCoreStyle::GetDefaultFontStyle("Bold", 30);

    ChildSlot
        [
            SNew(SBox)
                .Padding(25)
                .VAlign(VAlign_Bottom)
                [
                    // Agregamos el SBorder alrededor del STextBlock
                    SNew(SBorder)
                        .BorderBackgroundColor(FLinearColor::White)  // Color de fondo del borde
                        .BorderImage(FCoreStyle::Get().GetBrush("Border"))  // Usar el estilo predeterminado de borde
                        .Padding(5)  // Espacio entre el texto y el borde
                        [
                            SAssignNew(TextoBloque, STextBlock)
                                .Text(InArgs._DialogoTexto)
                                .Font(FontInfo)
                                .ColorAndOpacity(FSlateColor(FLinearColor::Green))
                                .Justification(ETextJustify::Right)
                                .ShadowColorAndOpacity(FLinearColor::Black)
                                .ShadowOffset(FVector2D(1.0f, 1.0f))
                                .LineHeightPercentage(1.2f)
                        ]
                ]
        ];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSSDialogoWidget::ActualizarTexto(FText NuevoTexto)
{
    if (TextoBloque.IsValid())
    {
        TextoBloque->SetText(NuevoTexto);
    }
}
