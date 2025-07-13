uint8_t IsMailEuropean(const struct MailMsg* de);
extern const char StandardEnglishFont[];
extern const char FrenchGermanFont[];
extern const char SpanishItalianFont[];
void ConvertFrenchGermanMailToEnglish(uint8_t* de);
void ConvertEnglishMailToFrenchGerman(uint8_t* de);
void ConvertSpanishItalianMailToEnglish(uint8_t* de);
void ConvertEnglishMailToSpanishItalian(uint8_t* de);
//#include "gfx/font/english.1bpp"
//#include "gfx/font/french_german.1bpp"
//#include "gfx/font/spanish_italian.1bpp"
