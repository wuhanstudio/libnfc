// To compile this simple example:
// $ gcc -o quick_start_example1 quick_start_example1.c -lnfc

#include <rtthread.h>
#include <stdlib.h>
#include <nfc/nfc.h>

static void
print_hex(const uint8_t *pbtData, const size_t szBytes)
{
  size_t  szPos;

  for (szPos = 0; szPos < szBytes; szPos++) {
    printf("%02x  ", pbtData[szPos]);
  }
  printf("\n");
}

int nfc_read_tag(int argc, const char *argv[])
{
  nfc_device *pnd;
  nfc_target nt;

  // nfc_context is not required

  // Display libnfc version
  const char *acLibnfcVersion = nfc_version();
  printf("%s uses libnfc %s\n", argv[0], acLibnfcVersion);

  // Open the device
  pnd = nfc_open("uart2");

  if (pnd == NULL) {
    printf("ERROR: %s\n", "Unable to open NFC device.");
    return -1;
  }

  // Set opened NFC device to initiator mode
  if (nfc_initiator_init(pnd) < 0) {
    return -2;
  }

  printf("NFC reader: %s opened\n", nfc_device_get_name(pnd));

  // Poll for a ISO14443A (MIFARE) tag
  const nfc_modulation nmMifare = {
    .nmt = NMT_ISO14443A,
    .nbr = NBR_106,
  };
  if (nfc_initiator_select_passive_target(pnd, nmMifare, NULL, 0, &nt) > 0) {
    printf("The following (NFC) ISO14443A tag was found:\n");
    printf("    ATQA (SENS_RES): ");
    print_hex(nt.nti.nai.abtAtqa, 2);
    printf("       UID (NFCID%c): ", (nt.nti.nai.abtUid[0] == 0x08 ? '3' : '1'));
    print_hex(nt.nti.nai.abtUid, nt.nti.nai.szUidLen);
    printf("      SAK (SEL_RES): ");
    print_hex(&nt.nti.nai.btSak, 1);
    if (nt.nti.nai.szAtsLen) {
      printf("          ATS (ATR): ");
      print_hex(nt.nti.nai.abtAts, nt.nti.nai.szAtsLen);
    }
  }

  // Close NFC device
  nfc_close(pnd);

  return 0;
}
MSH_CMD_EXPORT(nfc_read_tag, nfc read tag example)
