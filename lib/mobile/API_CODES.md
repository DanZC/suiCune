### API codes

A table containing information about the Mobile API functions.

| Code | Name | Desc | Input | Output | Used 
|------|------|------|-------|--------|------
|00|MobileAPI_00|Get Error Codes||a,h,l - Error codes|x
|01|MobileAPI_01|Starts communication?|de - Pointer value to set wc86e to<br/>hl - Value to set wc981 to<br/>bc - Value to set wc983 to||x
|02|MobileAPI_02|Something with writing config data?|||
|03|MobileAPI_03|Login to ISP?|hl - Login password||x
|04|MobileAPI_04|Dial phone number|hl - Phone number||x
|05|MobileAPI_05|End communication?|||x
|06|MobileAPI_06|Copies password?|de - Destination||x
|07|MobileAPI_07|Copies user id|de - Destination||x
|08|MobileAPI_08|Copies user email|de - Destination||x
|09|MobileAPI_09|Reset timer?|||x
|0A|MobileAPI_0A|POP HELO|?|?|
|0B|MobileAPI_0B|Something with POP header?|?|?|
|0C|MobileAPI_0C|POP DATA?|?|?|
|0D|MobileAPI_0D|POP QUIT? duplicate of 0E?|||
|0E|MobileAPI_0E|POP QUIT|||x
|0F|MobileAPI_0F|POP login|hl - String containing login info||x
|10|MobileAPI_10|POP STAT|de - Pointer value to set wc86e to||x
|11|MobileAPI_11|POP LIST|de - Pointer value to set wc86e to<br/> hl - message number||x
|12|MobileAPI_12|POP RETR|de - Pointer value to set wc86e to<br/> hl - message number<br/> bc - buffer size?||x
|13|MobileAPI_13|POP DELE|hl - message number||x
|14|MobileAPI_14|POP TOP|de - Pointer value to set wc827 to<br/> hl - message number<br/> bc - buffer size?||x
|15|MobileAPI_15|HTTP recv?|de - Destination?<br/> bc - Size<br/> hl - Pointers to config data||x
|16|MobileAPI_16|HTTP send?|de - Source?<br/> bc - Size<br/> hl - Pointers to config data||x
|17|MobileAPI_17|Copy to send packet|hl - Source|a = 0x0 on success, 0xff on failure|x
|18|MobileAPI_SetTimer|Sets GB timer for mobile communication|c - Timer value index||x
|19|MobileAPI_TelephoneStatus|Queries status of telephone line|de - Pointer value to set wc86e to||x
|1A|MobileAPI_1A|Reset packet buffer?|||
|1B|MobileAPI_1B|Clears MobileAPI data and resets packet buffer|||x
|1C|MobileAPI_1C|Reads config data?|||
|1D|MobileAPI_1D|Copy received packet|hl - Destination||x
|1E|MobileAPI_1E|???
|1F|MobileAPI_1F|Copy of MobileAPI_03|Same as MobileAPI_03|Same as MobileAPI_03
|20|MobileAPI_20|Copy of MobileAPI_01|Same as MobileAPI_01|Same as MobileAPI_01|x
|21|MobileAPI_21|Copy of MobileAPI_TelephoneStatus|Same as MobileAPI_TelephoneStatus|Same as MobileAPI_TelephoneStatus|x

### Config data

#### MobileAPI_15

|Offset|Desc|
|------|----|
|0x0|Some kind of destination for some data
|0x2|The pointer to the string containing the URL

#### MobileAPI_16

|Offset|Desc|
|------|----|
|0x0|Some kind of destination for some data
|0x2|Upload length
|0x4|Some kind of destination for some data
|0x6|The pointer to the string containing the URL

