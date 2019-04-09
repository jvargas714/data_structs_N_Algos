import algos 
import utility as ut 

headers = "IMSI,IMEI,TMSI,PTIMSI,MTIMSI,AUTH,ALLOW,CSSTA,PSSTA,IP,TECH,MSISDN,NAME,MAKE,MODEL,CSKEYGENMODE,CSAUTN,CSCIPH,CSIK,CSCK,CSKC,CSRAND,CSXRES,PSKEYGENMODE,PSAUTN,PSCIPH,PSIK,PSCK,PSKC,PSRAND,PSXRES,ORIGIN,UCKI,IMSREG,SMSoIP,IMSIPVERSION,AUTH_OP,AUTH_OPC,USER_DEFINED_OP,USER_DEFINED_OPC"
fmt = "%015I64x,%015I64x,0x%s,0x%s,0x%s,%s,%s,%d,%d,%d,%s,%I64x,%s,%s,%s,%s,0x%s,%s,0x%s,0x%s,0x%s,0x%s,0x%s,%s,0x%s,%s,0x%s,0x%s,0x%s,0x%s,0x%s,%s,0x%s,%d,%d,0x%s,0x%s,%d,%d"

hdrs = headers.split(',')
fmts = fmt.split(',')
print("headers length: ", len(hdrs))
print(hdrs, "\n\n\n\n")
print(f"fmt len:{len(fmts)}")
print(fmts)

hdrDict = {} 
i = 0
for header in hdrs:
	if i > len(fmts)-1:
		hdrDict[header] = "UNKNOWN!!!!!"
	else:
		hdrDict[header] = fmts[i]
	i += 1

print("\n\n\n\n")
for key, val in hdrDict.items():
	print(f"{key}:{val}")

