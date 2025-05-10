uint8_t IsMailEuropean(const struct MailMsg* de);
extern const char StandardEnglishFont[];
extern const char FrenchGermanFont[];
extern const char SpanishItalianFont[];
void ConvertFrenchGermanMailToEnglish(struct MailMsg* de);
void ConvertEnglishMailToFrenchGerman(struct MailMsg* de);
void ConvertSpanishItalianMailToEnglish(struct MailMsg* de);
void ConvertEnglishMailToSpanishItalian(struct MailMsg* de);
//#include "gfx/font/english.1bpp"
//#include "gfx/font/french_german.1bpp"
//#include "gfx/font/spanish_italian.1bpp"
