; Windows 3.89.1 original PE SHA-256: c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d
; Static excerpts from build/analysis/windows-3891-native-full.asm; addresses below are original VA.
; No game execution or tests.

; Native call 00447B94
  447b79:	75 e5                	jne    0x447b60
  447b7b:	69 fb 0c 02 00 00    	imul   edi,ebx,0x20c
  447b81:	68 04 75 59 00       	push   0x597504
  447b86:	6a 41                	push   0x41
  447b88:	68 08 5a 59 00       	push   0x595a08
  447b8d:	8d b7 88 f9 59 06    	lea    esi,[edi+0x659f988]
  447b93:	56                   	push   esi
  447b94:	e8 37 95 fb ff       	call   0x4010d0
  447b99:	83 c4 10             	add    esp,0x10
  447b9c:	8d 4e 01             	lea    ecx,[esi+0x1]

; Native call 00447C24
  447c09:	75 e7                	jne    0x447bf2
  447c0b:	69 fb 0c 02 00 00    	imul   edi,ebx,0x20c
  447c11:	68 0c 75 59 00       	push   0x59750c
  447c16:	6a 42                	push   0x42
  447c18:	68 08 5a 59 00       	push   0x595a08
  447c1d:	8d b7 88 f9 59 06    	lea    esi,[edi+0x659f988]
  447c23:	56                   	push   esi
  447c24:	e8 a7 94 fb ff       	call   0x4010d0
  447c29:	83 c4 10             	add    esp,0x10
  447c2c:	8d 4e 01             	lea    ecx,[esi+0x1]

; Native call 00447CB4
  447c99:	75 e7                	jne    0x447c82
  447c9b:	69 fb 0c 02 00 00    	imul   edi,ebx,0x20c
  447ca1:	68 18 75 59 00       	push   0x597518
  447ca6:	6a 43                	push   0x43
  447ca8:	68 08 5a 59 00       	push   0x595a08
  447cad:	8d b7 88 f9 59 06    	lea    esi,[edi+0x659f988]
  447cb3:	56                   	push   esi
  447cb4:	e8 17 94 fb ff       	call   0x4010d0
  447cb9:	83 c4 10             	add    esp,0x10
  447cbc:	8d 4e 01             	lea    ecx,[esi+0x1]

; Native call 00447D44
  447d29:	75 e7                	jne    0x447d12
  447d2b:	69 fb 0c 02 00 00    	imul   edi,ebx,0x20c
  447d31:	68 20 75 59 00       	push   0x597520
  447d36:	6a 46                	push   0x46
  447d38:	68 08 5a 59 00       	push   0x595a08
  447d3d:	8d b7 88 f9 59 06    	lea    esi,[edi+0x659f988]
  447d43:	56                   	push   esi
  447d44:	e8 87 93 fb ff       	call   0x4010d0
  447d49:	83 c4 10             	add    esp,0x10
  447d4c:	8d 4e 01             	lea    ecx,[esi+0x1]

; Native call 00447DD4
  447db9:	75 e7                	jne    0x447da2
  447dbb:	69 fb 0c 02 00 00    	imul   edi,ebx,0x20c
  447dc1:	68 28 75 59 00       	push   0x597528
  447dc6:	6a 48                	push   0x48
  447dc8:	68 08 5a 59 00       	push   0x595a08
  447dcd:	8d b7 88 f9 59 06    	lea    esi,[edi+0x659f988]
  447dd3:	56                   	push   esi
  447dd4:	e8 f7 92 fb ff       	call   0x4010d0
  447dd9:	83 c4 10             	add    esp,0x10
  447ddc:	8d 4e 01             	lea    ecx,[esi+0x1]

; Native call 00447E64
  447e49:	75 e7                	jne    0x447e32
  447e4b:	69 fb 0c 02 00 00    	imul   edi,ebx,0x20c
  447e51:	68 30 75 59 00       	push   0x597530
  447e56:	6a 4c                	push   0x4c
  447e58:	68 08 5a 59 00       	push   0x595a08
  447e5d:	8d b7 88 f9 59 06    	lea    esi,[edi+0x659f988]
  447e63:	56                   	push   esi
  447e64:	e8 67 92 fb ff       	call   0x4010d0
  447e69:	83 c4 10             	add    esp,0x10
  447e6c:	8d 4e 01             	lea    ecx,[esi+0x1]

; Native call 00447EF4
  447ed9:	75 e7                	jne    0x447ec2
  447edb:	69 fb 0c 02 00 00    	imul   edi,ebx,0x20c
  447ee1:	68 38 75 59 00       	push   0x597538
  447ee6:	6a 54                	push   0x54
  447ee8:	68 08 5a 59 00       	push   0x595a08
  447eed:	8d b7 88 f9 59 06    	lea    esi,[edi+0x659f988]
  447ef3:	56                   	push   esi
  447ef4:	e8 d7 91 fb ff       	call   0x4010d0
  447ef9:	83 c4 10             	add    esp,0x10
  447efc:	8d 4e 01             	lea    ecx,[esi+0x1]

; Native call 00447F84
  447f69:	75 e7                	jne    0x447f52
  447f6b:	69 fb 0c 02 00 00    	imul   edi,ebx,0x20c
  447f71:	68 44 75 59 00       	push   0x597544
  447f76:	6a 52                	push   0x52
  447f78:	68 08 5a 59 00       	push   0x595a08
  447f7d:	8d b7 88 f9 59 06    	lea    esi,[edi+0x659f988]
  447f83:	56                   	push   esi
  447f84:	e8 47 91 fb ff       	call   0x4010d0
  447f89:	83 c4 10             	add    esp,0x10
  447f8c:	8d 4e 01             	lea    ecx,[esi+0x1]

; Native call 00448014
  447ff9:	75 e7                	jne    0x447fe2
  447ffb:	69 fb 0c 02 00 00    	imul   edi,ebx,0x20c
  448001:	68 50 75 59 00       	push   0x597550
  448006:	6a 4f                	push   0x4f
  448008:	68 08 5a 59 00       	push   0x595a08
  44800d:	8d b7 88 f9 59 06    	lea    esi,[edi+0x659f988]
  448013:	56                   	push   esi
  448014:	e8 b7 90 fb ff       	call   0x4010d0
  448019:	83 c4 10             	add    esp,0x10
  44801c:	8d 4e 01             	lea    ecx,[esi+0x1]

; Native call 004480A4
  448089:	75 e7                	jne    0x448072
  44808b:	69 fb 0c 02 00 00    	imul   edi,ebx,0x20c
  448091:	68 5c 75 59 00       	push   0x59755c
  448096:	6a 55                	push   0x55
  448098:	68 08 5a 59 00       	push   0x595a08
  44809d:	8d b7 88 f9 59 06    	lea    esi,[edi+0x659f988]
  4480a3:	56                   	push   esi
  4480a4:	e8 27 90 fb ff       	call   0x4010d0
  4480a9:	83 c4 10             	add    esp,0x10
  4480ac:	8d 4e 01             	lea    ecx,[esi+0x1]

; Native call 00448134
  448119:	75 e7                	jne    0x448102
  44811b:	69 fb 0c 02 00 00    	imul   edi,ebx,0x20c
  448121:	68 70 75 59 00       	push   0x597570
  448126:	6a 59                	push   0x59
  448128:	68 08 5a 59 00       	push   0x595a08
  44812d:	8d b7 88 f9 59 06    	lea    esi,[edi+0x659f988]
  448133:	56                   	push   esi
  448134:	e8 97 8f fb ff       	call   0x4010d0
  448139:	83 c4 10             	add    esp,0x10
  44813c:	8d 4e 01             	lea    ecx,[esi+0x1]

; Native call 004481C4
  4481a9:	75 e7                	jne    0x448192
  4481ab:	69 fb 0c 02 00 00    	imul   edi,ebx,0x20c
  4481b1:	68 80 75 59 00       	push   0x597580
  4481b6:	6a 57                	push   0x57
  4481b8:	68 08 5a 59 00       	push   0x595a08
  4481bd:	8d b7 88 f9 59 06    	lea    esi,[edi+0x659f988]
  4481c3:	56                   	push   esi
  4481c4:	e8 07 8f fb ff       	call   0x4010d0
  4481c9:	83 c4 10             	add    esp,0x10
  4481cc:	8d 4e 01             	lea    ecx,[esi+0x1]

; Native call 00448254
  448239:	75 e7                	jne    0x448222
  44823b:	69 fb 0c 02 00 00    	imul   edi,ebx,0x20c
  448241:	68 88 75 59 00       	push   0x597588
  448246:	6a 58                	push   0x58
  448248:	68 08 5a 59 00       	push   0x595a08
  44824d:	8d b7 88 f9 59 06    	lea    esi,[edi+0x659f988]
  448253:	56                   	push   esi
  448254:	e8 77 8e fb ff       	call   0x4010d0
  448259:	83 c4 10             	add    esp,0x10
  44825c:	8d 4e 01             	lea    ecx,[esi+0x1]

; Native call 00448324
  448309:	75 e5                	jne    0x4482f0
  44830b:	69 fb 0c 02 00 00    	imul   edi,ebx,0x20c
  448311:	68 a0 75 59 00       	push   0x5975a0
  448316:	6a 2b                	push   0x2b
  448318:	68 08 5a 59 00       	push   0x595a08
  44831d:	8d b7 88 f9 59 06    	lea    esi,[edi+0x659f988]
  448323:	56                   	push   esi
  448324:	e8 a7 8d fb ff       	call   0x4010d0
  448329:	83 c4 10             	add    esp,0x10
  44832c:	8d 4e 01             	lea    ecx,[esi+0x1]

; Native call 00448376
  448357:	00 00 00 
  44835a:	a3 98 96 5a 06       	mov    ds:0x65a9698,eax
  44835f:	8b 45 84             	mov    eax,DWORD PTR [ebp-0x7c]
  448362:	b9 bc 75 59 00       	mov    ecx,0x5975bc
  448367:	c7 05 50 ba 5b 06 01 	mov    DWORD PTR ds:0x65bba50,0x1
  44836e:	00 00 00 
  448371:	a3 b4 4b 35 06       	mov    ds:0x6354bb4,eax
  448376:	e8 35 7f 0b 00       	call   0x5002b0
  44837b:	8b 3d b0 4a 35 06    	mov    edi,DWORD PTR ds:0x6354ab0
  448381:	8a d8                	mov    bl,al

; Native call 005003B8
  5003a0:	6a 06                	push   0x6
  5003a2:	53                   	push   ebx
  5003a3:	68 28 01 00 00       	push   0x128
  5003a8:	68 be 00 00 00       	push   0xbe
  5003ad:	68 f2 01 00 00       	push   0x1f2
  5003b2:	8d 54 24 4c          	lea    edx,[esp+0x4c]
  5003b6:	33 c9                	xor    ecx,ecx
  5003b8:	e8 d3 f3 fc ff       	call   0x4cf790
  5003bd:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  5003c2:	83 c4 14             	add    esp,0x14

; Native call 0050042B
  500412:	83 f9 ff             	cmp    ecx,0xffffffff
  500415:	75 0e                	jne    0x500425
  500417:	ba 16 c6 58 00       	mov    edx,0x58c616
  50041c:	33 c9                	xor    ecx,ecx
  50041e:	e8 6d f5 fc ff       	call   0x4cf990
  500423:	eb 1f                	jmp    0x500444
  500425:	8d 97 38 ff ff ff    	lea    edx,[edi-0xc8]
  50042b:	e8 60 f5 fc ff       	call   0x4cf990
  500430:	8b 44 24 0c          	mov    eax,DWORD PTR [esp+0xc]
  500434:	b9 01 00 00 00       	mov    ecx,0x1

; Native call 0050048C
  50046e:	81 c7 0c 02 00 00    	add    edi,0x20c
  500474:	3b 1d 98 96 5a 06    	cmp    ebx,DWORD PTR ds:0x65a9698
  50047a:	7c 94                	jl     0x500410
  50047c:	83 3d 94 96 5a 06 00 	cmp    DWORD PTR ds:0x65a9694,0x0
  500483:	75 1b                	jne    0x5004a0
  500485:	ba 16 c6 58 00       	mov    edx,0x58c616
  50048a:	33 c9                	xor    ecx,ecx
  50048c:	e8 ff f4 fc ff       	call   0x4cf990
  500491:	ba d8 5c 59 00       	mov    edx,0x595cd8
  500496:	b9 1b 00 00 00       	mov    ecx,0x1b

; Native call 0050049B
  50047c:	83 3d 94 96 5a 06 00 	cmp    DWORD PTR ds:0x65a9694,0x0
  500483:	75 1b                	jne    0x5004a0
  500485:	ba 16 c6 58 00       	mov    edx,0x58c616
  50048a:	33 c9                	xor    ecx,ecx
  50048c:	e8 ff f4 fc ff       	call   0x4cf990
  500491:	ba d8 5c 59 00       	mov    edx,0x595cd8
  500496:	b9 1b 00 00 00       	mov    ecx,0x1b
  50049b:	e8 f0 f4 fc ff       	call   0x4cf990
  5004a0:	8b 5c 24 0c          	mov    ebx,DWORD PTR [esp+0xc]
  5004a4:	c7 05 94 96 5a 06 00 	mov    DWORD PTR ds:0x65a9694,0x0

; Native call 00500525
  50050d:	6a 01                	push   0x1
  50050f:	68 a0 5a 00 00       	push   0x5aa0
  500514:	68 10 ef 34 06       	push   0x634ef10
  500519:	ff d6                	call   esi
  50051b:	57                   	push   edi
  50051c:	ff 15 b4 c4 58 00    	call   DWORD PTR ds:0x58c4b4
  500522:	83 c4 2c             	add    esp,0x2c
  500525:	e8 86 fa fc ff       	call   0x4cffb0
  50052a:	b9 b8 88 5a 06       	mov    ecx,0x65a88b8
  50052f:	8d 51 01             	lea    edx,[ecx+0x1]

; Native call 00500640
  500625:	8b f9                	mov    edi,ecx
  500627:	89 7c 24 14          	mov    DWORD PTR [esp+0x14],edi
  50062b:	eb 04                	jmp    0x500631
  50062d:	8b 7c 24 14          	mov    edi,DWORD PTR [esp+0x14]
  500631:	ba 1c ad 5a 00       	mov    edx,0x5aad1c
  500636:	b9 ac ec 59 00       	mov    ecx,0x59ecac
  50063b:	e8 10 08 00 00       	call   0x500e50
  500640:	e8 db 0a fd ff       	call   0x4d1120
  500645:	8b f0                	mov    esi,eax
  500647:	8d 44 24 38          	lea    eax,[esp+0x38]

; Native call 004D027F
  4d0268:	8b 0d 20 4a 35 06    	mov    ecx,DWORD PTR ds:0x6354a20
  4d026e:	8d 56 03             	lea    edx,[esi+0x3]
  4d0271:	83 c4 0c             	add    esp,0xc
  4d0274:	8d 49 05             	lea    ecx,[ecx+0x5]
  4d0277:	6a 00                	push   0x0
  4d0279:	53                   	push   ebx
  4d027a:	68 38 4a 35 06       	push   0x6354a38
  4d027f:	e8 1c e3 03 00       	call   0x50e5a0
  4d0284:	83 c4 0c             	add    esp,0xc
  4d0287:	a1 30 4a 35 06       	mov    eax,ds:0x6354a30

; Native call 004D031F
  4d0300:	8b 96 d4 00 00 00    	mov    edx,DWORD PTR [esi+0xd4]
  4d0306:	8b 8e d0 00 00 00    	mov    ecx,DWORD PTR [esi+0xd0]
  4d030c:	83 ea 06             	sub    edx,0x6
  4d030f:	a3 c4 ba 5b 06       	mov    ds:0x65bbac4,eax
  4d0314:	a1 9c 4a 35 06       	mov    eax,ds:0x6354a9c
  4d0319:	56                   	push   esi
  4d031a:	a3 54 ba 5b 06       	mov    ds:0x65bba54,eax
  4d031f:	e8 5c 43 04 00       	call   0x514680
  4d0324:	83 c4 04             	add    esp,0x4
  4d0327:	c7 05 c4 ba 5b 06 00 	mov    DWORD PTR ds:0x65bbac4,0x0

; Native call 005149F9
  5149df:	8b 95 64 ff ff ff    	mov    edx,DWORD PTR [ebp-0x9c]
  5149e5:	8d 4e 08             	lea    ecx,[esi+0x8]
  5149e8:	ff 35 c4 ba 5b 06    	push   DWORD PTR ds:0x65bbac4
  5149ee:	8b 85 58 ff ff ff    	mov    eax,DWORD PTR [ebp-0xa8]
  5149f4:	40                   	inc    eax
  5149f5:	50                   	push   eax
  5149f6:	8d 52 05             	lea    edx,[edx+0x5]
  5149f9:	e8 a2 9b ff ff       	call   0x50e5a0
  5149fe:	83 c4 0c             	add    esp,0xc
  514a01:	8b 4d f8             	mov    ecx,DWORD PTR [ebp-0x8]
