#include "GetCurrLanguage.h"

USING_NS_CC;

const char * GetCurrLanguage::getCurrLanguage(){

	auto languageType = CCApplication::sharedApplication()->getCurrentLanguage();

	if(kLanguageEnglish == languageType){
		return "languages/english.plist";
	}else if(kLanguageChinese == languageType){
		return "languages/english.plist";
	}else if(kLanguageFrench == languageType){
		return "languages/french.plist";
	}else if(kLanguageItalian == languageType){
		return "languages/english.plist";
	}else if(kLanguageGerman == languageType){
		return "languages/english.plist";
	}else if(kLanguageSpanish == languageType){
		return "languages/english.plist";
	}else if(kLanguageRussian == languageType){
		return "languages/english.plist";
	}else if(kLanguageKorean == languageType){
		return "languages/english.plist";
	}else if(kLanguageJapanese == languageType){
		return "languages/english.plist";
	}else if(kLanguageHungarian == languageType){
		return "languages/english.plist";
	}else if(kLanguagePortuguese == languageType){
		return "languages/english.plist";
	}else if(kLanguageArabic == languageType){
		return "languages/english.plist";
	}else{
		return "languages/english.plist";
	}






}