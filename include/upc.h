#ifndef UPC_H

#define UPC_H

#define MESSAGE_SUCCESSFUL_VALIDATION "\nThe barcode %d%d%d%d%d%d%d%d%d%d%d%d has been successfully validated.\n"
#define MESSAGE_VALIDATION_FAILURE "\nWarning: Barcode error encountered with barcode %d%d%d%d%d%d%d%d%d%d%d%d.\n"

#define PREFIX_0_1_6_7_8 "for most products"
#define PREFIX_2 "reserved for local use (store/warehouse), or for items sold by weight."
#define PREFIX_3 "drugs by National Drug Code number. Pharmaceuticals in the U.S. have the remainder of the UPC as their National Drug Code number."
#define PREFIX_4 "reserved for local use, often for loyalty cards or store coupons."
#define PREFIX_5_9 "coupons"
#define PREFIX_ERROR "ERROR: Cannot determine designation"

#define AUDIO_MEDIA_DIGIT_1 "Audio: 12\" LP or Single\t\tVideo: 12\" Video CDV"
#define AUDIO_MEDIA_DIGIT_2 "Audio: 3\" or 5\" CD, CD-ROM CDI and VCD\t\tVideo: Unassigned"
#define AUDIO_MEDIA_DIGIT_3 "Audio: Unassigned\t\tVideo: VHS"
#define AUDIO_MEDIA_DIGIT_4 "Audio: Cassette\t\tVideo: Unassigned"
#define AUDIO_MEDIA_DIGIT_5 "Audio: DCC\t\tVideo: Beta"
#define AUDIO_MEDIA_DIGIT_6 "Audio: Unassigned\t\tVideo: Laserdisk"
#define AUDIO_MEDIA_DIGIT_7 "Audio: 7\" Single\t\tVideo: Unassigned"
#define AUDIO_MEDIA_DIGIT_8 "Audio: Mini Disc\t\tVideo: 8mm Tape"
#define AUDIO_MEDIA_DIGIT_9 "Audio: Music DVD\t\tVideo: Video DVD"
#define AUDIO_MEDIA_DIGIT_0 "Audio: Unassigned\t\tVideo: Unassigned"
#define AUDIO_MEDIA_DIGIT_ERROR "UNABLE TO DETERMINE AUDIO MEDIA DIGIT"

#define MAX_BARCODE_ARRAY_SIZE 12


void print_barcode(int barcode_array[12]);

void readInUPCbarcode(int barcode_array[12]);

void calculateUPCcheckDigit(int barcode_array[12], int *check_digit);

int isCheckDigitLastDigit(int check_digit, int barcode_array[12]);

int foundDigitsOnly(int barcode_array[12]);

char *barcode_arr_to_string(int barcode_array[12]);

void print_UPC_designation(int barcode_array[12]);

char *getAudioVideoProductString(int barcode_array[12]);

void display_startup_banner();

void clear(void);

#endif
