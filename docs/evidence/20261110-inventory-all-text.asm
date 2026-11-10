; Offline Windows 3.89.1 PE extraction, image base 00400000.
; SHA-256 c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d
; Source: build/analysis/windows-3891-native-full.asm

  404066:	e8 25 87 0d 00       	call   0x4dc790
  40406b:	83 c4 08             	add    esp,0x8
  40406e:	85 c0                	test   eax,eax
  404070:	0f 85 fa 05 00 00    	jne    0x404670
  404076:	68 54 16 00 00       	push   0x1654
  40407b:	8d 84 24 14 03 00 00 	lea    eax,[esp+0x314]
  404082:	68 e8 a6 72 0a       	push   0xa72a6e8
  404087:	50                   	push   eax
  404088:	e8 13 75 18 00       	call   0x58b5a0
  40408d:	83 c4 0c             	add    esp,0xc
  404090:	b9 bc cb 58 00       	mov    ecx,0x58cbbc
  404095:	e8 66 da 15 00       	call   0x561b00
  40409a:	8b c8                	mov    ecx,eax
  40409c:	e8 6f 24 0f 00       	call   0x4f6510
  4040a1:	6a 00                	push   0x0
  4040a3:	6a 07                	push   0x7
  4040a5:	6a 40                	push   0x40
  4040a7:	68 c8 cb 58 00       	push   0x58cbc8
  4040ac:	68 d0 cb 58 00       	push   0x58cbd0
  4040b1:	ff 35 40 bd 72 0a    	push   DWORD PTR ds:0xa72bd40
  4040b7:	83 ca ff             	or     edx,0xffffffff
  4040ba:	ff 35 9c 1c 6d 0a    	push   DWORD PTR ds:0xa6d1c9c
  4040c0:	8d 4a 03             	lea    ecx,[edx+0x3]
  4040c3:	e8 98 0f 05 00       	call   0x455060
  4040c8:	8b d8                	mov    ebx,eax

  404db1:	0b c8                	or     ecx,eax
  404db3:	74 1b                	je     0x404dd0
  404db5:	b9 a8 ce 58 00       	mov    ecx,0x58cea8
  404dba:	e8 51 17 0f 00       	call   0x4f6510
  404dbf:	5f                   	pop    edi
  404dc0:	5e                   	pop    esi
  404dc1:	5b                   	pop    ebx
  404dc2:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  404dc5:	33 cd                	xor    ecx,ebp
  404dc7:	e8 e2 52 18 00       	call   0x58a0ae
  404dcc:	8b e5                	mov    esp,ebp
  404dce:	5d                   	pop    ebp
  404dcf:	c3                   	ret
  404dd0:	6a 00                	push   0x0
  404dd2:	6a 07                	push   0x7
  404dd4:	6a 40                	push   0x40
  404dd6:	68 04 cf 58 00       	push   0x58cf04
  404ddb:	68 10 cf 58 00       	push   0x58cf10
  404de0:	ff 35 40 bd 72 0a    	push   DWORD PTR ds:0xa72bd40
  404de6:	83 c8 ff             	or     eax,0xffffffff
  404de9:	ff 35 9c 1c 6d 0a    	push   DWORD PTR ds:0xa6d1c9c
  404def:	8b d0                	mov    edx,eax
  404df1:	8d 48 03             	lea    ecx,[eax+0x3]
  404df4:	e8 67 02 05 00       	call   0x455060
  404df9:	8b d8                	mov    ebx,eax

  405232:	e4 cf                	in     al,0xcf
  405234:	58                   	pop    eax
  405235:	00 b1 02 e8 e3 25    	add    BYTE PTR [ecx+0x25e3e802],dh
  40523b:	0f 00 8b 15 3c bd 72 	str    WORD PTR [ebx+0x72bd3c15]
  405242:	0a a1 34 1c 6d 0a    	or     ah,BYTE PTR [ecx+0xa6d1c34]
  405248:	85 d2                	test   edx,edx
  40524a:	75 08                	jne    0x405254
  40524c:	85 c0                	test   eax,eax
  40524e:	0f 84 ea 00 00 00    	je     0x40533e
  405254:	50                   	push   eax
  405255:	b9 1b 00 00 00       	mov    ecx,0x1b
  40525a:	e8 d1 41 01 00       	call   0x419430
  40525f:	83 c4 04             	add    esp,0x4
  405262:	83 f8 ff             	cmp    eax,0xffffffff
  405265:	75 0b                	jne    0x405272
  405267:	b9 fc cf 58 00       	mov    ecx,0x58cffc
  40526c:	5e                   	pop    esi
  40526d:	e9 9e 12 0f 00       	jmp    0x4f6510
  405272:	6a 00                	push   0x0
  405274:	6a 07                	push   0x7
  405276:	6a 40                	push   0x40
  405278:	ba 10 d0 58 00       	mov    edx,0x58d010
  40527d:	b9 24 d0 58 00       	mov    ecx,0x58d024
  405282:	e8 69 2f 05 00       	call   0x4581f0
  405287:	8b d0                	mov    edx,eax

  431437:	8d 49 01             	lea    ecx,[ecx+0x1]
  43143a:	88 44 0d 8f          	mov    BYTE PTR [ebp+ecx*1-0x71],al
  43143e:	84 c0                	test   al,al
  431440:	75 ee                	jne    0x431430
  431442:	8b ca                	mov    ecx,edx
  431444:	e8 f7 8d fe ff       	call   0x41a240
  431449:	8b bd 94 f6 ff ff    	mov    edi,DWORD PTR [ebp-0x96c]
  43144f:	8b 8d bc f6 ff ff    	mov    ecx,DWORD PTR [ebp-0x944]
  431455:	8b 85 b4 f6 ff ff    	mov    eax,DWORD PTR [ebp-0x94c]
  43145b:	43                   	inc    ebx
  43145c:	3b d8                	cmp    ebx,eax
  43145e:	7c 80                	jl     0x4313e0
  431460:	8b bd b0 f6 ff ff    	mov    edi,DWORD PTR [ebp-0x950]
  431466:	8b b5 a4 f6 ff ff    	mov    esi,DWORD PTR [ebp-0x95c]
  43146c:	85 ff                	test   edi,edi
  43146e:	79 75                	jns    0x4314e5
  431470:	ba 84 2d 59 00       	mov    edx,0x592d84
  431475:	6a 00                	push   0x0
  431477:	83 fe 01             	cmp    esi,0x1
  43147a:	75 1b                	jne    0x431497
  43147c:	68 40 00 00 80       	push   0x80000040
  431481:	6a 40                	push   0x40
  431483:	b9 90 2d 59 00       	mov    ecx,0x592d90
  431488:	e8 63 6d 02 00       	call   0x4581f0
  43148d:	8b f8                	mov    edi,eax

  43144f:	8b 8d bc f6 ff ff    	mov    ecx,DWORD PTR [ebp-0x944]
  431455:	8b 85 b4 f6 ff ff    	mov    eax,DWORD PTR [ebp-0x94c]
  43145b:	43                   	inc    ebx
  43145c:	3b d8                	cmp    ebx,eax
  43145e:	7c 80                	jl     0x4313e0
  431460:	8b bd b0 f6 ff ff    	mov    edi,DWORD PTR [ebp-0x950]
  431466:	8b b5 a4 f6 ff ff    	mov    esi,DWORD PTR [ebp-0x95c]
  43146c:	85 ff                	test   edi,edi
  43146e:	79 75                	jns    0x4314e5
  431470:	ba 84 2d 59 00       	mov    edx,0x592d84
  431475:	6a 00                	push   0x0
  431477:	83 fe 01             	cmp    esi,0x1
  43147a:	75 1b                	jne    0x431497
  43147c:	68 40 00 00 80       	push   0x80000040
  431481:	6a 40                	push   0x40
  431483:	b9 90 2d 59 00       	mov    ecx,0x592d90
  431488:	e8 63 6d 02 00       	call   0x4581f0
  43148d:	8b f8                	mov    edi,eax
  43148f:	89 bd b0 f6 ff ff    	mov    DWORD PTR [ebp-0x950],edi
  431495:	eb 19                	jmp    0x4314b0
  431497:	68 42 00 00 80       	push   0x80000042
  43149c:	6a 40                	push   0x40
  43149e:	b9 a0 2d 59 00       	mov    ecx,0x592da0
  4314a3:	e8 48 6d 02 00       	call   0x4581f0
  4314a8:	8b f8                	mov    edi,eax

  431a6e:	8b ce                	mov    ecx,esi
  431a70:	e8 3b 0f 0f 00       	call   0x5229b0
  431a75:	89 85 bc f6 ff ff    	mov    DWORD PTR [ebp-0x944],eax
  431a7b:	83 c4 08             	add    esp,0x8
  431a7e:	a1 e0 b8 72 0a       	mov    eax,ds:0xa72b8e0
  431a83:	80 3d e6 bc 72 0a 03 	cmp    BYTE PTR ds:0xa72bce6,0x3
  431a8a:	75 21                	jne    0x431aad
  431a8c:	39 05 f4 10 61 0a    	cmp    DWORD PTR ds:0xa6110f4,eax
  431a92:	76 19                	jbe    0x431aad
  431a94:	6a fd                	push   0xfffffffd
  431a96:	68 b0 05 59 00       	push   0x5905b0
  431a9b:	8b d3                	mov    edx,ebx
  431a9d:	8b ce                	mov    ecx,esi
  431a9f:	e8 0c 0f 0f 00       	call   0x5229b0
  431aa4:	83 c4 08             	add    esp,0x8
  431aa7:	89 85 bc f6 ff ff    	mov    DWORD PTR [ebp-0x944],eax
  431aad:	b9 80 2f 59 00       	mov    ecx,0x592f80
  431ab2:	e8 59 4a 0c 00       	call   0x4f6510
  431ab7:	6a 00                	push   0x0
  431ab9:	6a 07                	push   0x7
  431abb:	6a 40                	push   0x40
  431abd:	ba b4 2f 59 00       	mov    edx,0x592fb4
  431ac2:	b9 24 d0 58 00       	mov    ecx,0x58d024
  431ac7:	e8 24 67 02 00       	call   0x4581f0
  431acc:	8b d8                	mov    ebx,eax

  435a62:	8b e5                	mov    esp,ebp
  435a64:	5d                   	pop    ebp
  435a65:	c3                   	ret
  435a66:	cc                   	int3
  435a67:	cc                   	int3
  435a68:	cc                   	int3
  435a69:	cc                   	int3
  435a6a:	cc                   	int3
  435a6b:	cc                   	int3
  435a6c:	cc                   	int3
  435a6d:	cc                   	int3
  435a6e:	cc                   	int3
  435a6f:	cc                   	int3
  435a70:	51                   	push   ecx
  435a71:	6a 00                	push   0x0
  435a73:	6a 07                	push   0x7
  435a75:	6a 40                	push   0x40
  435a77:	68 f0 35 59 00       	push   0x5935f0
  435a7c:	68 58 3b 59 00       	push   0x593b58
  435a81:	ff 35 40 bd 72 0a    	push   DWORD PTR ds:0xa72bd40
  435a87:	83 ca ff             	or     edx,0xffffffff
  435a8a:	ff 35 9c 1c 6d 0a    	push   DWORD PTR ds:0xa6d1c9c
  435a90:	8d 4a 03             	lea    ecx,[edx+0x3]
  435a93:	e8 c8 f5 01 00       	call   0x455060
  435a98:	83 c4 1c             	add    esp,0x1c

  43629b:	3b f0                	cmp    esi,eax
  43629d:	0f 8e 3d ff ff ff    	jle    0x4361e0
  4362a3:	eb 21                	jmp    0x4362c6
  4362a5:	b9 f8 3b 59 00       	mov    ecx,0x593bf8
  4362aa:	e8 f1 55 0c 00       	call   0x4fb8a0
  4362af:	84 c0                	test   al,al
  4362b1:	0f 85 ac 00 00 00    	jne    0x436363
  4362b7:	8b 1d 40 bd 72 0a    	mov    ebx,DWORD PTR ds:0xa72bd40
  4362bd:	8b 0d 9c 1c 6d 0a    	mov    ecx,DWORD PTR ds:0xa6d1c9c
  4362c3:	8d 7b 01             	lea    edi,[ebx+0x1]
  4362c6:	47                   	inc    edi
  4362c7:	8d 43 01             	lea    eax,[ebx+0x1]
  4362ca:	3b f8                	cmp    edi,eax
  4362cc:	0f 8e ee fe ff ff    	jle    0x4361c0
  4362d2:	6a 00                	push   0x0
  4362d4:	6a 03                	push   0x3
  4362d6:	6a 40                	push   0x40
  4362d8:	68 10 3c 59 00       	push   0x593c10
  4362dd:	68 18 3c 59 00       	push   0x593c18
  4362e2:	83 ca ff             	or     edx,0xffffffff
  4362e5:	53                   	push   ebx
  4362e6:	51                   	push   ecx
  4362e7:	8d 4a 03             	lea    ecx,[edx+0x3]
  4362ea:	e8 71 ed 01 00       	call   0x455060
  4362ef:	83 c4 1c             	add    esp,0x1c

  43b428:	bb 02 00 00 00       	mov    ebx,0x2
  43b42d:	85 c0                	test   eax,eax
  43b42f:	0f 89 1a 01 00 00    	jns    0x43b54f
  43b435:	6a 00                	push   0x0
  43b437:	51                   	push   ecx
  43b438:	8d 4b 40             	lea    ecx,[ebx+0x40]
  43b43b:	e8 40 08 fe ff       	call   0x41bc80
  43b440:	83 c4 08             	add    esp,0x8
  43b443:	85 c0                	test   eax,eax
  43b445:	0f 89 04 01 00 00    	jns    0x43b54f
  43b44b:	b9 30 44 59 00       	mov    ecx,0x594430
  43b450:	e8 bb b0 0b 00       	call   0x4f6510
  43b455:	6a 00                	push   0x0
  43b457:	68 80 08 00 80       	push   0x80000880
  43b45c:	6a 40                	push   0x40
  43b45e:	68 70 44 59 00       	push   0x594470
  43b463:	68 78 44 59 00       	push   0x594478
  43b468:	ff 35 40 bd 72 0a    	push   DWORD PTR ds:0xa72bd40
  43b46e:	83 ca ff             	or     edx,0xffffffff
  43b471:	c7 05 a0 30 6f 00 00 	mov    DWORD PTR ds:0x6f30a0,0x0
  43b478:	00 00 00 
  43b47b:	ff 35 9c 1c 6d 0a    	push   DWORD PTR ds:0xa6d1c9c
  43b481:	8b cb                	mov    ecx,ebx
  43b483:	e8 d8 9b 01 00       	call   0x455060
  43b488:	8b c8                	mov    ecx,eax

  443d45:	57                   	push   edi
  443d46:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  443d4c:	c7 85 f8 fb ff ff 6e 	mov    DWORD PTR [ebp-0x408],0x74656e
  443d53:	65 74 00 
  443d56:	6a 00                	push   0x0
  443d58:	50                   	push   eax
  443d59:	e8 d2 7c fd ff       	call   0x41ba30
  443d5e:	83 c4 08             	add    esp,0x8
  443d61:	3d 18 fc ff ff       	cmp    eax,0xfffffc18
  443d66:	74 19                	je     0x443d81
  443d68:	8d 04 c0             	lea    eax,[eax+eax*8]
  443d6b:	80 3c 85 b8 28 6d 0a 	cmp    BYTE PTR [eax*4+0xa6d28b8],0x21
  443d72:	21 
  443d73:	75 0c                	jne    0x443d81
  443d75:	33 d2                	xor    edx,edx
  443d77:	0f 57 d2             	xorps  xmm2,xmm2
  443d7a:	33 c9                	xor    ecx,ecx
  443d7c:	e9 28 02 00 00       	jmp    0x443fa9
  443d81:	6a 00                	push   0x0
  443d83:	6a 06                	push   0x6
  443d85:	6a 40                	push   0x40
  443d87:	ba 18 6b 59 00       	mov    edx,0x596b18
  443d8c:	b9 20 6b 59 00       	mov    ecx,0x596b20
  443d91:	e8 5a 44 01 00       	call   0x4581f0
  443d96:	8b d8                	mov    ebx,eax

  444000:	89 45 98             	mov    DWORD PTR [ebp-0x68],eax
  444003:	66 a1 bc 6b 59 00    	mov    ax,ds:0x596bbc
  444009:	68 c0 6b 59 00       	push   0x596bc0
  44400e:	6a 03                	push   0x3
  444010:	66 0f d6 45 90       	movq   QWORD PTR [ebp-0x70],xmm0
  444015:	66 89 45 9c          	mov    WORD PTR [ebp-0x64],ax
  444019:	e8 72 87 09 00       	call   0x4dc790
  44401e:	83 c4 08             	add    esp,0x8
  444021:	85 c0                	test   eax,eax
  444023:	0f 85 b8 04 00 00    	jne    0x4444e1
  444029:	83 3d 40 56 35 06 00 	cmp    DWORD PTR ds:0x6355640,0x0
  444030:	b8 3c 00 00 00       	mov    eax,0x3c
  444035:	6a 00                	push   0x0
  444037:	68 42 00 00 80       	push   0x80000042
  44403c:	6a 40                	push   0x40
  44403e:	68 d0 6b 59 00       	push   0x596bd0
  444043:	68 e8 6b 59 00       	push   0x596be8
  444048:	ff 35 40 bd 72 0a    	push   DWORD PTR ds:0xa72bd40
  44404e:	0f 45 d8             	cmovne ebx,eax
  444051:	8d 48 c6             	lea    ecx,[eax-0x3a]
  444054:	ff 35 9c 1c 6d 0a    	push   DWORD PTR ds:0xa6d1c9c
  44405a:	83 ca ff             	or     edx,0xffffffff
  44405d:	89 9d 7c fb ff ff    	mov    DWORD PTR [ebp-0x484],ebx
  444063:	e8 f8 0f 01 00       	call   0x455060
  444068:	8b d8                	mov    ebx,eax

  444539:	8d 53 e3             	lea    edx,[ebx-0x1d]
  44453c:	83 c9 ff             	or     ecx,0xffffffff
  44453f:	68 40 6d 59 00       	push   0x596d40
  444544:	6a 03                	push   0x3
  444546:	e8 45 82 09 00       	call   0x4dc790
  44454b:	83 c4 08             	add    esp,0x8
  44454e:	85 c0                	test   eax,eax
  444550:	0f 85 a7 04 00 00    	jne    0x4449fd
  444556:	83 3d 40 56 35 06 00 	cmp    DWORD PTR ds:0x6355640,0x0
  44455d:	b8 5a 00 00 00       	mov    eax,0x5a
  444562:	b9 58 6d 59 00       	mov    ecx,0x596d58
  444567:	0f 45 d8             	cmovne ebx,eax
  44456a:	89 9d c8 fe ff ff    	mov    DWORD PTR [ebp-0x138],ebx
  444570:	e8 9b 1f 0b 00       	call   0x4f6510
  444575:	6a 00                	push   0x0
  444577:	68 42 00 00 80       	push   0x80000042
  44457c:	6a 40                	push   0x40
  44457e:	68 b4 6d 59 00       	push   0x596db4
  444583:	68 bc 6d 59 00       	push   0x596dbc
  444588:	ff 35 40 bd 72 0a    	push   DWORD PTR ds:0xa72bd40
  44458e:	83 ca ff             	or     edx,0xffffffff
  444591:	ff 35 9c 1c 6d 0a    	push   DWORD PTR ds:0xa6d1c9c
  444597:	8d 4a 03             	lea    ecx,[edx+0x3]
  44459a:	e8 c1 0a 01 00       	call   0x455060
  44459f:	8b d0                	mov    edx,eax

  445676:	e8 85 c4 11 00       	call   0x561b00
  44567b:	50                   	push   eax
  44567c:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  445682:	50                   	push   eax
  445683:	e8 48 ba fb ff       	call   0x4010d0
  445688:	83 c4 10             	add    esp,0x10
  44568b:	8d 8d f8 fb ff ff    	lea    ecx,[ebp-0x408]
  445691:	e8 7a 0e 0b 00       	call   0x4f6510
  445696:	8d 8d 51 fb ff ff    	lea    ecx,[ebp-0x4af]
  44569c:	e8 0f fa ff ff       	call   0x4450b0
  4456a1:	89 85 34 fb ff ff    	mov    DWORD PTR [ebp-0x4cc],eax
  4456a7:	85 c0                	test   eax,eax
  4456a9:	0f 85 ca 01 00 00    	jne    0x445879
  4456af:	b9 3c 6b 59 00       	mov    ecx,0x596b3c
  4456b4:	89 35 4c 28 62 0a    	mov    DWORD PTR ds:0xa62284c,esi
  4456ba:	e8 41 c4 11 00       	call   0x561b00
  4456bf:	8b c8                	mov    ecx,eax
  4456c1:	e9 db 04 00 00       	jmp    0x445ba1
  4456c6:	6a 00                	push   0x0
  4456c8:	6a 02                	push   0x2
  4456ca:	6a 40                	push   0x40
  4456cc:	ba 18 6b 59 00       	mov    edx,0x596b18
  4456d1:	b9 bc 6e 59 00       	mov    ecx,0x596ebc
  4456d6:	e8 15 2b 01 00       	call   0x4581f0
  4456db:	83 c4 0c             	add    esp,0xc

  44717a:	cc                   	int3
  44717b:	cc                   	int3
  44717c:	cc                   	int3
  44717d:	cc                   	int3
  44717e:	cc                   	int3
  44717f:	cc                   	int3
  447180:	55                   	push   ebp
  447181:	8b ec                	mov    ebp,esp
  447183:	81 ec 84 05 00 00    	sub    esp,0x584
  447189:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  44718e:	33 c5                	xor    eax,ebp
  447190:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  447193:	53                   	push   ebx
  447194:	56                   	push   esi
  447195:	57                   	push   edi
  447196:	6a 00                	push   0x0
  447198:	0f 57 c0             	xorps  xmm0,xmm0
  44719b:	ba 74 71 59 00       	mov    edx,0x597174
  4471a0:	68 40 40 00 80       	push   0x80004040
  4471a5:	6a 60                	push   0x60
  4471a7:	b9 7c 71 59 00       	mov    ecx,0x59717c
  4471ac:	f3 0f 11 85 f4 fb ff 	movss  DWORD PTR [ebp-0x40c],xmm0
  4471b3:	ff 
  4471b4:	e8 37 10 01 00       	call   0x4581f0
  4471b9:	8b d8                	mov    ebx,eax

  447627:	cc                   	int3
  447628:	cc                   	int3
  447629:	cc                   	int3
  44762a:	cc                   	int3
  44762b:	cc                   	int3
  44762c:	cc                   	int3
  44762d:	cc                   	int3
  44762e:	cc                   	int3
  44762f:	cc                   	int3
  447630:	55                   	push   ebp
  447631:	8b ec                	mov    ebp,esp
  447633:	81 ec 24 06 00 00    	sub    esp,0x624
  447639:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  44763e:	33 c5                	xor    eax,ebp
  447640:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  447643:	53                   	push   ebx
  447644:	56                   	push   esi
  447645:	57                   	push   edi
  447646:	6a 00                	push   0x0
  447648:	68 40 40 00 80       	push   0x80004040
  44764d:	6a 60                	push   0x60
  44764f:	ba d4 72 59 00       	mov    edx,0x5972d4
  447654:	b9 dc 72 59 00       	mov    ecx,0x5972dc
  447659:	e8 92 0b 01 00       	call   0x4581f0
  44765e:	8b d8                	mov    ebx,eax

  447747:	6a 04                	push   0x4
  447749:	e8 22 a0 00 00       	call   0x451770
  44774e:	83 c4 04             	add    esp,0x4
  447751:	50                   	push   eax
  447752:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  447758:	68 8c 73 59 00       	push   0x59738c
  44775d:	50                   	push   eax
  44775e:	e8 6d 99 fb ff       	call   0x4010d0
  447763:	83 c4 0c             	add    esp,0xc
  447766:	8d 8d f8 fb ff ff    	lea    ecx,[ebp-0x408]
  44776c:	e8 9f ed 0a 00       	call   0x4f6510
  447771:	6a 00                	push   0x0
  447773:	b9 0e 00 00 00       	mov    ecx,0xe
  447778:	e8 93 7c 08 00       	call   0x4cf410
  44777d:	b9 06 00 00 00       	mov    ecx,0x6
  447782:	8b d0                	mov    edx,eax
  447784:	e8 87 7c 08 00       	call   0x4cf410
  447789:	0b d0                	or     edx,eax
  44778b:	b9 bc 73 59 00       	mov    ecx,0x5973bc
  447790:	81 ca 00 00 00 80    	or     edx,0x80000000
  447796:	52                   	push   edx
  447797:	6a 60                	push   0x60
  447799:	ba d4 72 59 00       	mov    edx,0x5972d4
  44779e:	e8 4d 0a 01 00       	call   0x4581f0
  4477a3:	83 c4 0c             	add    esp,0xc

  44cc80:	55                   	push   ebp
  44cc81:	8b ec                	mov    ebp,esp
  44cc83:	83 ec 18             	sub    esp,0x18
  44cc86:	53                   	push   ebx
  44cc87:	56                   	push   esi
  44cc88:	57                   	push   edi
  44cc89:	8b da                	mov    ebx,edx
  44cc8b:	8b f9                	mov    edi,ecx
  44cc8d:	32 c0                	xor    al,al
  44cc8f:	89 5d f4             	mov    DWORD PTR [ebp-0xc],ebx
  44cc92:	89 7d f8             	mov    DWORD PTR [ebp-0x8],edi
  44cc95:	33 f6                	xor    esi,esi
  44cc97:	89 45 f0             	mov    DWORD PTR [ebp-0x10],eax
  44cc9a:	e8 b1 1d ff ff       	call   0x43ea50
  44cc9f:	68 be 02 00 00       	push   0x2be
  44cca4:	56                   	push   esi
  44cca5:	68 85 00 00 00       	push   0x85
  44ccaa:	68 48 86 59 00       	push   0x598648
  44ccaf:	68 50 86 59 00       	push   0x598650
  44ccb4:	53                   	push   ebx
  44ccb5:	57                   	push   edi
  44ccb6:	83 ca ff             	or     edx,0xffffffff
  44ccb9:	8d 4e 01             	lea    ecx,[esi+0x1]
  44ccbc:	e8 9f 83 00 00       	call   0x455060
  44ccc1:	83 c4 1c             	add    esp,0x1c

  44cd6d:	83 fe 01             	cmp    esi,0x1
  44cd70:	0f 84 c0 01 00 00    	je     0x44cf36
  44cd76:	8b 5d f4             	mov    ebx,DWORD PTR [ebp-0xc]
  44cd79:	8b d3                	mov    edx,ebx
  44cd7b:	8b 75 f8             	mov    esi,DWORD PTR [ebp-0x8]
  44cd7e:	51                   	push   ecx
  44cd7f:	8b ce                	mov    ecx,esi
  44cd81:	e8 ea f0 fc ff       	call   0x41be70
  44cd86:	83 c4 04             	add    esp,0x4
  44cd89:	85 c0                	test   eax,eax
  44cd8b:	74 0a                	je     0x44cd97
  44cd8d:	80 7d ff 00          	cmp    BYTE PTR [ebp-0x1],0x0
  44cd91:	0f 84 9f 01 00 00    	je     0x44cf36
  44cd97:	68 be 02 00 00       	push   0x2be
  44cd9c:	6a 00                	push   0x0
  44cd9e:	6a 05                	push   0x5
  44cda0:	68 48 86 59 00       	push   0x598648
  44cda5:	68 50 86 59 00       	push   0x598650
  44cdaa:	53                   	push   ebx
  44cdab:	bb 01 00 00 00       	mov    ebx,0x1
  44cdb0:	83 ca ff             	or     edx,0xffffffff
  44cdb3:	56                   	push   esi
  44cdb4:	8b cb                	mov    ecx,ebx
  44cdb6:	e8 a5 82 00 00       	call   0x455060
  44cdbb:	83 c4 1c             	add    esp,0x1c

  44d00d:	cc                   	int3
  44d00e:	cc                   	int3
  44d00f:	cc                   	int3
  44d010:	55                   	push   ebp
  44d011:	8b ec                	mov    ebp,esp
  44d013:	81 ec 44 02 00 00    	sub    esp,0x244
  44d019:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  44d01e:	33 c5                	xor    eax,ebp
  44d020:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  44d023:	53                   	push   ebx
  44d024:	8b d9                	mov    ebx,ecx
  44d026:	c7 45 f8 00 00 00 00 	mov    DWORD PTR [ebp-0x8],0x0
  44d02d:	89 5d f0             	mov    DWORD PTR [ebp-0x10],ebx
  44d030:	c7 45 f4 00 00 00 00 	mov    DWORD PTR [ebp-0xc],0x0
  44d037:	56                   	push   esi
  44d038:	57                   	push   edi
  44d039:	81 fb 18 fc ff ff    	cmp    ebx,0xfffffc18
  44d03f:	75 52                	jne    0x44d093
  44d041:	68 c3 01 00 00       	push   0x1c3
  44d046:	6a 03                	push   0x3
  44d048:	6a 40                	push   0x40
  44d04a:	ba 7c 87 59 00       	mov    edx,0x59877c
  44d04f:	b9 84 87 59 00       	mov    ecx,0x598784
  44d054:	e8 97 b1 00 00       	call   0x4581f0
  44d059:	8b d8                	mov    ebx,eax

  44dea7:	80 bd 18 fe ff ff 01 	cmp    BYTE PTR [ebp-0x1e8],0x1
  44deae:	b8 02 00 00 00       	mov    eax,0x2
  44deb3:	0f 44 d8             	cmove  ebx,eax
  44deb6:	33 c9                	xor    ecx,ecx
  44deb8:	39 8d 54 fd ff ff    	cmp    DWORD PTR [ebp-0x2ac],ecx
  44debe:	0f 95 c1             	setne  cl
  44dec1:	33 c0                	xor    eax,eax
  44dec3:	85 db                	test   ebx,ebx
  44dec5:	0f 95 c0             	setne  al
  44dec8:	85 c8                	test   eax,ecx
  44deca:	74 19                	je     0x44dee5
  44decc:	8b cb                	mov    ecx,ebx
  44dece:	e8 fd 14 ff ff       	call   0x43f3d0
  44ded3:	33 f6                	xor    esi,esi
  44ded5:	8b d8                	mov    ebx,eax
  44ded7:	89 9d 64 fd ff ff    	mov    DWORD PTR [ebp-0x29c],ebx
  44dedd:	8d 46 01             	lea    eax,[esi+0x1]
  44dee0:	e9 bc 01 00 00       	jmp    0x44e0a1
  44dee5:	6a 00                	push   0x0
  44dee7:	6a 00                	push   0x0
  44dee9:	6a 30                	push   0x30
  44deeb:	ba 58 89 59 00       	mov    edx,0x598958
  44def0:	b9 64 89 59 00       	mov    ecx,0x598964
  44def5:	e8 f6 a2 00 00       	call   0x4581f0
  44defa:	8b d8                	mov    ebx,eax

  45031a:	cc                   	int3
  45031b:	cc                   	int3
  45031c:	cc                   	int3
  45031d:	cc                   	int3
  45031e:	cc                   	int3
  45031f:	cc                   	int3
  450320:	55                   	push   ebp
  450321:	8b ec                	mov    ebp,esp
  450323:	81 ec 6c 05 00 00    	sub    esp,0x56c
  450329:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  45032e:	33 c5                	xor    eax,ebp
  450330:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  450333:	53                   	push   ebx
  450334:	8b d9                	mov    ebx,ecx
  450336:	56                   	push   esi
  450337:	57                   	push   edi
  450338:	81 fb 18 fc ff ff    	cmp    ebx,0xfffffc18
  45033e:	75 4c                	jne    0x45038c
  450340:	6a 00                	push   0x0
  450342:	6a 00                	push   0x0
  450344:	6a 00                	push   0x0
  450346:	ba 14 79 59 00       	mov    edx,0x597914
  45034b:	b9 50 8d 59 00       	mov    ecx,0x598d50
  450350:	e8 9b 7e 00 00       	call   0x4581f0
  450355:	8b d8                	mov    ebx,eax

  4504c8:	e8 03 ac 13 00       	call   0x58b0d0
  4504cd:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  4504d2:	33 c5                	xor    eax,ebp
  4504d4:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  4504d7:	53                   	push   ebx
  4504d8:	56                   	push   esi
  4504d9:	57                   	push   edi
  4504da:	68 54 16 00 00       	push   0x1654
  4504df:	8d 85 f8 e1 ff ff    	lea    eax,[ebp-0x1e08]
  4504e5:	8b d9                	mov    ebx,ecx
  4504e7:	68 e8 a6 72 0a       	push   0xa72a6e8
  4504ec:	50                   	push   eax
  4504ed:	e8 ae b0 13 00       	call   0x58b5a0
  4504f2:	83 c4 0c             	add    esp,0xc
  4504f5:	b9 14 55 59 00       	mov    ecx,0x595514
  4504fa:	e8 01 16 11 00       	call   0x561b00
  4504ff:	8b c8                	mov    ecx,eax
  450501:	e8 0a 60 0a 00       	call   0x4f6510
  450506:	6a 00                	push   0x0
  450508:	68 88 00 00 80       	push   0x80000088
  45050d:	68 40 20 00 00       	push   0x2040
  450512:	ba 20 55 59 00       	mov    edx,0x595520
  450517:	b9 38 55 59 00       	mov    ecx,0x595538
  45051c:	e8 cf 7c 00 00       	call   0x4581f0
  450521:	83 c4 0c             	add    esp,0xc

  4505d7:	e9 5f 05 00 00       	jmp    0x450b3b
  4505dc:	8d 85 81 fa ff ff    	lea    eax,[ebp-0x57f]
  4505e2:	89 15 4c 28 62 0a    	mov    DWORD PTR ds:0xa62284c,edx
  4505e8:	50                   	push   eax
  4505e9:	ff 15 00 c5 58 00    	call   DWORD PTR ds:0x58c500
  4505ef:	83 c4 04             	add    esp,0x4
  4505f2:	b9 7c 55 59 00       	mov    ecx,0x59557c
  4505f7:	50                   	push   eax
  4505f8:	e8 03 15 11 00       	call   0x561b00
  4505fd:	50                   	push   eax
  4505fe:	8d 85 28 fb ff ff    	lea    eax,[ebp-0x4d8]
  450604:	50                   	push   eax
  450605:	e8 c6 0a fb ff       	call   0x4010d0
  45060a:	83 c4 0c             	add    esp,0xc
  45060d:	8d 8d 28 fb ff ff    	lea    ecx,[ebp-0x4d8]
  450613:	e8 f8 5e 0a 00       	call   0x4f6510
  450618:	81 fb 18 fc ff ff    	cmp    ebx,0xfffffc18
  45061e:	75 22                	jne    0x450642
  450620:	6a 00                	push   0x0
  450622:	6a 00                	push   0x0
  450624:	6a 00                	push   0x0
  450626:	ba 8c 55 59 00       	mov    edx,0x59558c
  45062b:	b9 98 55 59 00       	mov    ecx,0x595598
  450630:	e8 bb 7b 00 00       	call   0x4581f0
  450635:	8b d8                	mov    ebx,eax

  45804a:	cc                   	int3
  45804b:	cc                   	int3
  45804c:	cc                   	int3
  45804d:	cc                   	int3
  45804e:	cc                   	int3
  45804f:	cc                   	int3
  458050:	55                   	push   ebp
  458051:	8b ec                	mov    ebp,esp
  458053:	81 ec 08 04 00 00    	sub    esp,0x408
  458059:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  45805e:	33 c5                	xor    eax,ebp
  458060:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  458063:	56                   	push   esi
  458064:	57                   	push   edi
  458065:	68 a8 01 00 00       	push   0x1a8
  45806a:	6a 00                	push   0x0
  45806c:	6a 31                	push   0x31
  45806e:	68 18 5e 59 00       	push   0x595e18
  458073:	68 20 5e 59 00       	push   0x595e20
  458078:	ff 35 40 bd 72 0a    	push   DWORD PTR ds:0xa72bd40
  45807e:	83 ca ff             	or     edx,0xffffffff
  458081:	ff 35 9c 1c 6d 0a    	push   DWORD PTR ds:0xa6d1c9c
  458087:	8d 4a 03             	lea    ecx,[edx+0x3]
  45808a:	e8 d1 cf ff ff       	call   0x455060
  45808f:	83 c4 1c             	add    esp,0x1c

  458310:	5d                   	pop    ebp
  458311:	c3                   	ret
  458312:	a0 e6 bc 72 0a       	mov    al,ds:0xa72bce6
  458317:	3c 02                	cmp    al,0x2
  458319:	0f 84 2c 01 00 00    	je     0x45844b
  45831f:	3c 04                	cmp    al,0x4
  458321:	0f 84 24 01 00 00    	je     0x45844b
  458327:	b9 84 5e 59 00       	mov    ecx,0x595e84
  45832c:	e8 df e1 09 00       	call   0x4f6510
  458331:	e8 2a 3e 03 00       	call   0x48c160
  458336:	85 c0                	test   eax,eax
  458338:	74 0a                	je     0x458344
  45833a:	b9 78 88 5d 00       	mov    ecx,0x5d8878
  45833f:	e9 74 01 00 00       	jmp    0x4584b8
  458344:	6a 00                	push   0x0
  458346:	6a 00                	push   0x0
  458348:	6a 01                	push   0x1
  45834a:	68 b8 5e 59 00       	push   0x595eb8
  45834f:	68 c4 5e 59 00       	push   0x595ec4
  458354:	ff 35 40 bd 72 0a    	push   DWORD PTR ds:0xa72bd40
  45835a:	33 d2                	xor    edx,edx
  45835c:	ff 35 9c 1c 6d 0a    	push   DWORD PTR ds:0xa6d1c9c
  458362:	8d 4a 01             	lea    ecx,[edx+0x1]
  458365:	e8 f6 cc ff ff       	call   0x455060
  45836a:	83 c4 1c             	add    esp,0x1c

  4584b3:	b9 54 5e 59 00       	mov    ecx,0x595e54
  4584b8:	e8 53 e0 09 00       	call   0x4f6510
  4584bd:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  4584c0:	5f                   	pop    edi
  4584c1:	33 cd                	xor    ecx,ebp
  4584c3:	5e                   	pop    esi
  4584c4:	e8 e5 1b 13 00       	call   0x58a0ae
  4584c9:	8b e5                	mov    esp,ebp
  4584cb:	5d                   	pop    ebp
  4584cc:	c3                   	ret
  4584cd:	cc                   	int3
  4584ce:	cc                   	int3
  4584cf:	cc                   	int3
  4584d0:	56                   	push   esi
  4584d1:	68 a4 01 00 00       	push   0x1a4
  4584d6:	6a 02                	push   0x2
  4584d8:	6a 53                	push   0x53
  4584da:	68 c8 59 59 00       	push   0x5959c8
  4584df:	68 6c 5f 59 00       	push   0x595f6c
  4584e4:	ff 35 40 bd 72 0a    	push   DWORD PTR ds:0xa72bd40
  4584ea:	83 ca ff             	or     edx,0xffffffff
  4584ed:	ff 35 9c 1c 6d 0a    	push   DWORD PTR ds:0xa6d1c9c
  4584f3:	8d 4a 03             	lea    ecx,[edx+0x3]
  4584f6:	e8 65 cb ff ff       	call   0x455060
  4584fb:	83 c4 1c             	add    esp,0x1c

  45867a:	cc                   	int3
  45867b:	cc                   	int3
  45867c:	cc                   	int3
  45867d:	cc                   	int3
  45867e:	cc                   	int3
  45867f:	cc                   	int3
  458680:	55                   	push   ebp
  458681:	8b ec                	mov    ebp,esp
  458683:	83 ec 0c             	sub    esp,0xc
  458686:	53                   	push   ebx
  458687:	56                   	push   esi
  458688:	57                   	push   edi
  458689:	8b f9                	mov    edi,ecx
  45868b:	89 55 f8             	mov    DWORD PTR [ebp-0x8],edx
  45868e:	83 ce ff             	or     esi,0xffffffff
  458691:	33 db                	xor    ebx,ebx
  458693:	81 ff 18 fc ff ff    	cmp    edi,0xfffffc18
  458699:	75 28                	jne    0x4586c3
  45869b:	68 a7 01 00 00       	push   0x1a7
  4586a0:	68 42 00 00 80       	push   0x80000042
  4586a5:	6a 20                	push   0x20
  4586a7:	ba 88 5f 59 00       	mov    edx,0x595f88
  4586ac:	b9 90 5f 59 00       	mov    ecx,0x595f90
  4586b1:	e8 3a fb ff ff       	call   0x4581f0
  4586b6:	8b f8                	mov    edi,eax

  45880d:	e8 7e 24 08 00       	call   0x4dac90
  458812:	e8 79 aa 0a 00       	call   0x503290
  458817:	5f                   	pop    edi
  458818:	5e                   	pop    esi
  458819:	5b                   	pop    ebx
  45881a:	8b e5                	mov    esp,ebp
  45881c:	5d                   	pop    ebp
  45881d:	c3                   	ret
  45881e:	b9 ac 5f 59 00       	mov    ecx,0x595fac
  458823:	e8 e8 dc 09 00       	call   0x4f6510
  458828:	5f                   	pop    edi
  458829:	5e                   	pop    esi
  45882a:	5b                   	pop    ebx
  45882b:	8b e5                	mov    esp,ebp
  45882d:	5d                   	pop    ebp
  45882e:	c3                   	ret
  45882f:	cc                   	int3
  458830:	56                   	push   esi
  458831:	68 aa 01 00 00       	push   0x1aa
  458836:	6a 00                	push   0x0
  458838:	6a 01                	push   0x1
  45883a:	ba dc 5f 59 00       	mov    edx,0x595fdc
  45883f:	b9 e8 5f 59 00       	mov    ecx,0x595fe8
  458844:	e8 a7 f9 ff ff       	call   0x4581f0
  458849:	83 c4 0c             	add    esp,0xc

  458ce5:	8d 48 88             	lea    ecx,[eax-0x78]
  458ce8:	eb 1c                	jmp    0x458d06
  458cea:	83 f8 78             	cmp    eax,0x78
  458ced:	75 0b                	jne    0x458cfa
  458cef:	83 7d d0 00          	cmp    DWORD PTR [ebp-0x30],0x0
  458cf3:	74 18                	je     0x458d0d
  458cf5:	8d 48 89             	lea    ecx,[eax-0x77]
  458cf8:	eb 0c                	jmp    0x458d06
  458cfa:	3d cd 00 00 00       	cmp    eax,0xcd
  458cff:	75 0c                	jne    0x458d0d
  458d01:	b9 08 00 00 00       	mov    ecx,0x8
  458d06:	e8 05 67 07 00       	call   0x4cf410
  458d0b:	0b d8                	or     ebx,eax
  458d0d:	83 c2 04             	add    edx,0x4
  458d10:	81 fa 60 ae 72 0a    	cmp    edx,0xa72ae60
  458d16:	7c 9e                	jl     0x458cb6
  458d18:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [eax+eax*1+0x0]
  458d1f:	00 
  458d20:	68 8e 03 00 00       	push   0x38e
  458d25:	53                   	push   ebx
  458d26:	68 00 20 00 00       	push   0x2000
  458d2b:	ba e8 60 59 00       	mov    edx,0x5960e8
  458d30:	b9 f0 60 59 00       	mov    ecx,0x5960f0
  458d35:	e8 b6 f4 ff ff       	call   0x4581f0
  458d3a:	b9 30 2c 6f 00       	mov    ecx,0x6f2c30

  458e29:	cc                   	int3
  458e2a:	cc                   	int3
  458e2b:	cc                   	int3
  458e2c:	cc                   	int3
  458e2d:	cc                   	int3
  458e2e:	cc                   	int3
  458e2f:	cc                   	int3
  458e30:	55                   	push   ebp
  458e31:	8b ec                	mov    ebp,esp
  458e33:	83 e4 f8             	and    esp,0xfffffff8
  458e36:	51                   	push   ecx
  458e37:	56                   	push   esi
  458e38:	6a 00                	push   0x0
  458e3a:	6a 00                	push   0x0
  458e3c:	6a 00                	push   0x0
  458e3e:	68 0c 61 59 00       	push   0x59610c
  458e43:	68 28 61 59 00       	push   0x596128
  458e48:	ff 35 40 bd 72 0a    	push   DWORD PTR ds:0xa72bd40
  458e4e:	83 ca ff             	or     edx,0xffffffff
  458e51:	c7 05 a0 30 6f 00 00 	mov    DWORD PTR ds:0x6f30a0,0x0
  458e58:	00 00 00 
  458e5b:	ff 35 9c 1c 6d 0a    	push   DWORD PTR ds:0xa6d1c9c
  458e61:	8d 4a 03             	lea    ecx,[edx+0x3]
  458e64:	e8 f7 c1 ff ff       	call   0x455060
  458e69:	8b f0                	mov    esi,eax

  458ec3:	89 55 e0             	mov    DWORD PTR [ebp-0x20],edx
  458ec6:	0f 57 d2             	xorps  xmm2,xmm2
  458ec9:	c7 45 f0 18 fc ff ff 	mov    DWORD PTR [ebp-0x10],0xfffffc18
  458ed0:	f3 0f 11 55 f4       	movss  DWORD PTR [ebp-0xc],xmm2
  458ed5:	c7 45 ec 00 00 00 00 	mov    DWORD PTR [ebp-0x14],0x0
  458edc:	53                   	push   ebx
  458edd:	56                   	push   esi
  458ede:	57                   	push   edi
  458edf:	85 c9                	test   ecx,ecx
  458ee1:	0f 85 23 03 00 00    	jne    0x45920a
  458ee7:	b9 50 61 59 00       	mov    ecx,0x596150
  458eec:	e8 0f 8c 10 00       	call   0x561b00
  458ef1:	8b c8                	mov    ecx,eax
  458ef3:	e8 18 d6 09 00       	call   0x4f6510
  458ef8:	6a 00                	push   0x0
  458efa:	6a 00                	push   0x0
  458efc:	68 80 00 00 00       	push   0x80
  458f01:	68 16 c6 58 00       	push   0x58c616
  458f06:	68 16 c6 58 00       	push   0x58c616
  458f0b:	ff 35 40 bd 72 0a    	push   DWORD PTR ds:0xa72bd40
  458f11:	33 d2                	xor    edx,edx
  458f13:	ff 35 9c 1c 6d 0a    	push   DWORD PTR ds:0xa6d1c9c
  458f19:	8d 4a 01             	lea    ecx,[edx+0x1]
  458f1c:	e8 3f c1 ff ff       	call   0x455060
  458f21:	8b f0                	mov    esi,eax

  458f94:	8b d8                	mov    ebx,eax
  458f96:	83 c4 04             	add    esp,0x4
  458f99:	89 5d e8             	mov    DWORD PTR [ebp-0x18],ebx
  458f9c:	85 db                	test   ebx,ebx
  458f9e:	78 4d                	js     0x458fed
  458fa0:	8b cb                	mov    ecx,ebx
  458fa2:	e8 39 11 05 00       	call   0x4aa0e0
  458fa7:	85 c0                	test   eax,eax
  458fa9:	74 4a                	je     0x458ff5
  458fab:	b9 74 61 59 00       	mov    ecx,0x596174
  458fb0:	89 1d 4c 2a 62 0a    	mov    DWORD PTR ds:0xa622a4c,ebx
  458fb6:	e8 45 8b 10 00       	call   0x561b00
  458fbb:	8b c8                	mov    ecx,eax
  458fbd:	e8 4e d5 09 00       	call   0x4f6510
  458fc2:	6a 00                	push   0x0
  458fc4:	6a 00                	push   0x0
  458fc6:	6a 05                	push   0x5
  458fc8:	68 8c 61 59 00       	push   0x59618c
  458fcd:	68 94 61 59 00       	push   0x596194
  458fd2:	ff 35 40 bd 72 0a    	push   DWORD PTR ds:0xa72bd40
  458fd8:	33 d2                	xor    edx,edx
  458fda:	ff 35 9c 1c 6d 0a    	push   DWORD PTR ds:0xa6d1c9c
  458fe0:	8d 4a 01             	lea    ecx,[edx+0x1]
  458fe3:	e8 78 c0 ff ff       	call   0x455060
  458fe8:	83 c4 1c             	add    esp,0x1c

  458fd2:	ff 35 40 bd 72 0a    	push   DWORD PTR ds:0xa72bd40
  458fd8:	33 d2                	xor    edx,edx
  458fda:	ff 35 9c 1c 6d 0a    	push   DWORD PTR ds:0xa6d1c9c
  458fe0:	8d 4a 01             	lea    ecx,[edx+0x1]
  458fe3:	e8 78 c0 ff ff       	call   0x455060
  458fe8:	83 c4 1c             	add    esp,0x1c
  458feb:	8b f0                	mov    esi,eax
  458fed:	81 fb 18 fc ff ff    	cmp    ebx,0xfffffc18
  458ff3:	75 08                	jne    0x458ffd
  458ff5:	83 cb ff             	or     ebx,0xffffffff
  458ff8:	89 5d e8             	mov    DWORD PTR [ebp-0x18],ebx
  458ffb:	eb 05                	jmp    0x459002
  458ffd:	83 fb ff             	cmp    ebx,0xffffffff
  459000:	75 2b                	jne    0x45902d
  459002:	6a 00                	push   0x0
  459004:	6a 00                	push   0x0
  459006:	6a 05                	push   0x5
  459008:	68 b4 61 59 00       	push   0x5961b4
  45900d:	68 bc 61 59 00       	push   0x5961bc
  459012:	ff 35 40 bd 72 0a    	push   DWORD PTR ds:0xa72bd40
  459018:	33 d2                	xor    edx,edx
  45901a:	ff 35 9c 1c 6d 0a    	push   DWORD PTR ds:0xa6d1c9c
  459020:	8d 4a 01             	lea    ecx,[edx+0x1]
  459023:	e8 38 c0 ff ff       	call   0x455060
  459028:	83 c4 1c             	add    esp,0x1c

  469209:	00 00 
  46920b:	eb 1d                	jmp    0x46922a
  46920d:	8b cb                	mov    ecx,ebx
  46920f:	e8 0c ae 06 00       	call   0x4d4020
  469214:	50                   	push   eax
  469215:	8d 84 24 fc 0e 00 00 	lea    eax,[esp+0xefc]
  46921c:	68 f8 a9 59 00       	push   0x59a9f8
  469221:	50                   	push   eax
  469222:	e8 a9 7e f9 ff       	call   0x4010d0
  469227:	83 c4 0c             	add    esp,0xc
  46922a:	8d 8c 24 f8 0e 00 00 	lea    ecx,[esp+0xef8]
  469231:	e8 da d2 08 00       	call   0x4f6510
  469236:	6a 00                	push   0x0
  469238:	57                   	push   edi
  469239:	56                   	push   esi
  46923a:	68 38 aa 59 00       	push   0x59aa38
  46923f:	68 3c aa 59 00       	push   0x59aa3c
  469244:	ff 35 40 bd 72 0a    	push   DWORD PTR ds:0xa72bd40
  46924a:	83 ca ff             	or     edx,0xffffffff
  46924d:	c7 05 a0 30 6f 00 00 	mov    DWORD PTR ds:0x6f30a0,0x0
  469254:	00 00 00 
  469257:	ff 35 9c 1c 6d 0a    	push   DWORD PTR ds:0xa6d1c9c
  46925d:	8d 4a 03             	lea    ecx,[edx+0x3]
  469260:	e8 fb bd fe ff       	call   0x455060
  469265:	8b d8                	mov    ebx,eax

  4ab54e:	0f 84 b5 00 00 00    	je     0x4ab609
  4ab554:	80 b8 01 14 15 06 09 	cmp    BYTE PTR [eax+0x6151401],0x9
  4ab55b:	74 0d                	je     0x4ab56a
  4ab55d:	83 b8 60 14 15 06 ff 	cmp    DWORD PTR [eax+0x6151460],0xffffffff
  4ab564:	0f 85 9f 00 00 00    	jne    0x4ab609
  4ab56a:	b9 64 01 5a 00       	mov    ecx,0x5a0164
  4ab56f:	89 1d 4c 2a 62 0a    	mov    DWORD PTR ds:0xa622a4c,ebx
  4ab575:	e8 86 65 0b 00       	call   0x561b00
  4ab57a:	8b c8                	mov    ecx,eax
  4ab57c:	e8 8f af 04 00       	call   0x4f6510
  4ab581:	68 58 02 00 00       	push   0x258
  4ab586:	6a 00                	push   0x0
  4ab588:	6a 01                	push   0x1
  4ab58a:	68 74 01 5a 00       	push   0x5a0174
  4ab58f:	68 7c 01 5a 00       	push   0x5a017c
  4ab594:	8b cb                	mov    ecx,ebx
  4ab596:	e8 25 db f6 ff       	call   0x4190c0
  4ab59b:	50                   	push   eax
  4ab59c:	8b cb                	mov    ecx,ebx
  4ab59e:	e8 cd da f6 ff       	call   0x419070
  4ab5a3:	50                   	push   eax
  4ab5a4:	8b d3                	mov    edx,ebx
  4ab5a6:	b9 02 00 00 00       	mov    ecx,0x2
  4ab5ab:	e8 b0 9a fa ff       	call   0x455060
  4ab5b0:	83 c4 1c             	add    esp,0x1c

  4e8d80:	b9 f0 89 5a 00       	mov    ecx,0x5a89f0
  4e8d85:	e8 86 d7 00 00       	call   0x4f6510
  4e8d8a:	33 c0                	xor    eax,eax
  4e8d8c:	5f                   	pop    edi
  4e8d8d:	5e                   	pop    esi
  4e8d8e:	5b                   	pop    ebx
  4e8d8f:	8b 8c 24 78 05 00 00 	mov    ecx,DWORD PTR [esp+0x578]
  4e8d96:	33 cc                	xor    ecx,esp
  4e8d98:	e8 11 13 0a 00       	call   0x58a0ae
  4e8d9d:	8b e5                	mov    esp,ebp
  4e8d9f:	5d                   	pop    ebp
  4e8da0:	c3                   	ret
  4e8da1:	6a 00                	push   0x0
  4e8da3:	68 80 04 00 80       	push   0x80000480
  4e8da8:	6a 40                	push   0x40
  4e8daa:	68 40 8a 5a 00       	push   0x5a8a40
  4e8daf:	68 4c 8a 5a 00       	push   0x5a8a4c
  4e8db4:	ff 35 40 bd 72 0a    	push   DWORD PTR ds:0xa72bd40
  4e8dba:	83 ca ff             	or     edx,0xffffffff
  4e8dbd:	c7 05 a0 30 6f 00 00 	mov    DWORD PTR ds:0x6f30a0,0x0
  4e8dc4:	00 00 00 
  4e8dc7:	ff 35 9c 1c 6d 0a    	push   DWORD PTR ds:0xa6d1c9c
  4e8dcd:	8d 4a 03             	lea    ecx,[edx+0x3]
  4e8dd0:	e8 8b c2 f6 ff       	call   0x455060
  4e8dd5:	8b d8                	mov    ebx,eax

  51dc7e:	33 c5                	xor    eax,ebp
  51dc80:	89 45 f8             	mov    DWORD PTR [ebp-0x8],eax
  51dc83:	53                   	push   ebx
  51dc84:	56                   	push   esi
  51dc85:	57                   	push   edi
  51dc86:	6a 64                	push   0x64
  51dc88:	8d 85 24 ff ff ff    	lea    eax,[ebp-0xdc]
  51dc8e:	c6 85 6b f3 ff ff 00 	mov    BYTE PTR [ebp-0xc95],0x0
  51dc95:	6a 00                	push   0x0
  51dc97:	50                   	push   eax
  51dc98:	e8 c3 d1 06 00       	call   0x58ae60
  51dc9d:	83 c4 0c             	add    esp,0xc
  51dca0:	8d 45 8c             	lea    eax,[ebp-0x74]
  51dca3:	6a 64                	push   0x64
  51dca5:	6a 00                	push   0x0
  51dca7:	50                   	push   eax
  51dca8:	e8 b3 d1 06 00       	call   0x58ae60
  51dcad:	83 c4 0c             	add    esp,0xc
  51dcb0:	ba 10 de 5a 00       	mov    edx,0x5ade10
  51dcb5:	b9 18 de 5a 00       	mov    ecx,0x5ade18
  51dcba:	6a 00                	push   0x0
  51dcbc:	6a 05                	push   0x5
  51dcbe:	6a 40                	push   0x40
  51dcc0:	e8 2b a5 f3 ff       	call   0x4581f0
  51dcc5:	8b d8                	mov    ebx,eax

  51e14c:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  51e151:	33 c4                	xor    eax,esp
  51e153:	89 84 24 30 0c 00 00 	mov    DWORD PTR [esp+0xc30],eax
  51e15a:	53                   	push   ebx
  51e15b:	56                   	push   esi
  51e15c:	57                   	push   edi
  51e15d:	68 00 04 00 00       	push   0x400
  51e162:	8d 84 24 3c 08 00 00 	lea    eax,[esp+0x83c]
  51e169:	6a 00                	push   0x0
  51e16b:	50                   	push   eax
  51e16c:	e8 ef cc 06 00       	call   0x58ae60
  51e171:	83 c4 0c             	add    esp,0xc
  51e174:	8d 84 24 38 04 00 00 	lea    eax,[esp+0x438]
  51e17b:	68 00 04 00 00       	push   0x400
  51e180:	6a 00                	push   0x0
  51e182:	50                   	push   eax
  51e183:	e8 d8 cc 06 00       	call   0x58ae60
  51e188:	83 c4 0c             	add    esp,0xc
  51e18b:	ba ec de 5a 00       	mov    edx,0x5adeec
  51e190:	b9 f4 de 5a 00       	mov    ecx,0x5adef4
  51e195:	6a 00                	push   0x0
  51e197:	6a 05                	push   0x5
  51e199:	6a 40                	push   0x40
  51e19b:	e8 50 a0 f3 ff       	call   0x4581f0
  51e1a0:	8b f0                	mov    esi,eax

  51e5b1:	8b ec                	mov    ebp,esp
  51e5b3:	83 e4 c0             	and    esp,0xffffffc0
  51e5b6:	81 ec b4 0c 00 00    	sub    esp,0xcb4
  51e5bc:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  51e5c1:	33 c4                	xor    eax,esp
  51e5c3:	89 84 24 b0 0c 00 00 	mov    DWORD PTR [esp+0xcb0],eax
  51e5ca:	53                   	push   ebx
  51e5cb:	56                   	push   esi
  51e5cc:	57                   	push   edi
  51e5cd:	b9 2b 00 00 00       	mov    ecx,0x2b
  51e5d2:	e8 b9 4b 04 00       	call   0x563190
  51e5d7:	8d 94 24 88 0b 00 00 	lea    edx,[esp+0xb88]
  51e5de:	2b d0                	sub    edx,eax
  51e5e0:	8a 08                	mov    cl,BYTE PTR [eax]
  51e5e2:	8d 40 01             	lea    eax,[eax+0x1]
  51e5e5:	88 4c 02 ff          	mov    BYTE PTR [edx+eax*1-0x1],cl
  51e5e9:	84 c9                	test   cl,cl
  51e5eb:	75 f3                	jne    0x51e5e0
  51e5ed:	6a 00                	push   0x0
  51e5ef:	6a 05                	push   0x5
  51e5f1:	6a 40                	push   0x40
  51e5f3:	ba a0 df 5a 00       	mov    edx,0x5adfa0
  51e5f8:	b9 a8 df 5a 00       	mov    ecx,0x5adfa8
  51e5fd:	e8 ee 9b f3 ff       	call   0x4581f0
  51e602:	8b d8                	mov    ebx,eax

  51ecf3:	89 7c 24 5c          	mov    DWORD PTR [esp+0x5c],edi
  51ecf7:	e8 14 14 fa ff       	call   0x4c0110
  51ecfc:	f3 0f 10 05 c8 52 91 	movss  xmm0,DWORD PTR ds:0x59152c8
  51ed03:	05 
  51ed04:	f3 0f 11 44 24 50    	movss  DWORD PTR [esp+0x50],xmm0
  51ed0a:	80 3d b1 52 91 05 ff 	cmp    BYTE PTR ds:0x59152b1,0xff
  51ed11:	0f 85 c8 00 00 00    	jne    0x51eddf
  51ed17:	b9 3c cf 58 00       	mov    ecx,0x58cf3c
  51ed1c:	e8 ef 77 fd ff       	call   0x4f6510
  51ed21:	5f                   	pop    edi
  51ed22:	5e                   	pop    esi
  51ed23:	5b                   	pop    ebx
  51ed24:	8b 8c 24 70 10 00 00 	mov    ecx,DWORD PTR [esp+0x1070]
  51ed2b:	33 cc                	xor    ecx,esp
  51ed2d:	e8 7c b3 06 00       	call   0x58a0ae
  51ed32:	8b e5                	mov    esp,ebp
  51ed34:	5d                   	pop    ebp
  51ed35:	c3                   	ret
  51ed36:	6a 00                	push   0x0
  51ed38:	6a 05                	push   0x5
  51ed3a:	6a 40                	push   0x40
  51ed3c:	ba 18 e0 5a 00       	mov    edx,0x5ae018
  51ed41:	b9 1c e0 5a 00       	mov    ecx,0x5ae01c
  51ed46:	e8 a5 94 f3 ff       	call   0x4581f0
  51ed4b:	83 c4 0c             	add    esp,0xc

  520347:	1b ff                	sbb    edi,edi
  520349:	83 e7 0a             	and    edi,0xa
  52034c:	81 c7 18 01 00 00    	add    edi,0x118
  520352:	89 7c 24 28          	mov    DWORD PTR [esp+0x28],edi
  520356:	68 54 16 00 00       	push   0x1654
  52035b:	8d 84 24 64 02 00 00 	lea    eax,[esp+0x264]
  520362:	68 e8 a6 72 0a       	push   0xa72a6e8
  520367:	50                   	push   eax
  520368:	e8 33 b2 06 00       	call   0x58b5a0
  52036d:	83 c4 0c             	add    esp,0xc
  520370:	83 7c 24 30 00       	cmp    DWORD PTR [esp+0x30],0x0
  520375:	0f 85 b1 03 00 00    	jne    0x52072c
  52037b:	6a 00                	push   0x0
  52037d:	81 ff 18 01 00 00    	cmp    edi,0x118
  520383:	75 0e                	jne    0x520393
  520385:	6a 0b                	push   0xb
  520387:	ba 60 e6 5a 00       	mov    edx,0x5ae660
  52038c:	b9 68 e6 5a 00       	mov    ecx,0x5ae668
  520391:	eb 0c                	jmp    0x52039f
  520393:	6a 06                	push   0x6
  520395:	ba 90 e6 5a 00       	mov    edx,0x5ae690
  52039a:	b9 a0 e6 5a 00       	mov    ecx,0x5ae6a0
  52039f:	6a 60                	push   0x60
  5203a1:	e8 4a 7e f3 ff       	call   0x4581f0
  5203a6:	83 c4 0c             	add    esp,0xc

  520a39:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  520a3e:	33 c5                	xor    eax,ebp
  520a40:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  520a43:	53                   	push   ebx
  520a44:	56                   	push   esi
  520a45:	57                   	push   edi
  520a46:	b9 19 01 00 00       	mov    ecx,0x119
  520a4b:	e8 40 27 04 00       	call   0x563190
  520a50:	8d 75 90             	lea    esi,[ebp-0x70]
  520a53:	89 85 60 f5 ff ff    	mov    DWORD PTR [ebp-0xaa0],eax
  520a59:	8b d0                	mov    edx,eax
  520a5b:	2b f0                	sub    esi,eax
  520a5d:	0f 1f 00             	nop    DWORD PTR [eax]
  520a60:	8a 0a                	mov    cl,BYTE PTR [edx]
  520a62:	8d 52 01             	lea    edx,[edx+0x1]
  520a65:	88 4c 16 ff          	mov    BYTE PTR [esi+edx*1-0x1],cl
  520a69:	84 c9                	test   cl,cl
  520a6b:	75 f3                	jne    0x520a60
  520a6d:	6a 00                	push   0x0
  520a6f:	6a 0b                	push   0xb
  520a71:	68 40 02 00 00       	push   0x240
  520a76:	ba 9c e8 5a 00       	mov    edx,0x5ae89c
  520a7b:	b9 a0 e8 5a 00       	mov    ecx,0x5ae8a0
  520a80:	e8 6b 77 f3 ff       	call   0x4581f0
  520a85:	83 c4 0c             	add    esp,0xc

  520e41:	8b ec                	mov    ebp,esp
  520e43:	83 e4 c0             	and    esp,0xffffffc0
  520e46:	81 ec f4 0f 00 00    	sub    esp,0xff4
  520e4c:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  520e51:	33 c4                	xor    eax,esp
  520e53:	89 84 24 f0 0f 00 00 	mov    DWORD PTR [esp+0xff0],eax
  520e5a:	53                   	push   ebx
  520e5b:	56                   	push   esi
  520e5c:	57                   	push   edi
  520e5d:	b9 1b 01 00 00       	mov    ecx,0x11b
  520e62:	e8 29 23 04 00       	call   0x563190
  520e67:	8d 94 24 90 0b 00 00 	lea    edx,[esp+0xb90]
  520e6e:	2b d0                	sub    edx,eax
  520e70:	8a 08                	mov    cl,BYTE PTR [eax]
  520e72:	8d 40 01             	lea    eax,[eax+0x1]
  520e75:	88 4c 02 ff          	mov    BYTE PTR [edx+eax*1-0x1],cl
  520e79:	84 c9                	test   cl,cl
  520e7b:	75 f3                	jne    0x520e70
  520e7d:	6a 00                	push   0x0
  520e7f:	6a 0b                	push   0xb
  520e81:	68 40 02 00 00       	push   0x240
  520e86:	ba 2c ea 5a 00       	mov    edx,0x5aea2c
  520e8b:	b9 40 ea 5a 00       	mov    ecx,0x5aea40
  520e90:	e8 5b 73 f3 ff       	call   0x4581f0
  520e95:	83 c4 0c             	add    esp,0xc

  52141c:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  521421:	33 c4                	xor    eax,esp
  521423:	89 84 24 f0 0b 00 00 	mov    DWORD PTR [esp+0xbf0],eax
  52142a:	53                   	push   ebx
  52142b:	56                   	push   esi
  52142c:	0f 57 c0             	xorps  xmm0,xmm0
  52142f:	b9 24 01 00 00       	mov    ecx,0x124
  521434:	57                   	push   edi
  521435:	f3 0f 11 44 24 30    	movss  DWORD PTR [esp+0x30],xmm0
  52143b:	e8 50 1d 04 00       	call   0x563190
  521440:	8d 94 24 90 0b 00 00 	lea    edx,[esp+0xb90]
  521447:	2b d0                	sub    edx,eax
  521449:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [eax+0x0]
  521450:	8a 08                	mov    cl,BYTE PTR [eax]
  521452:	8d 40 01             	lea    eax,[eax+0x1]
  521455:	88 4c 02 ff          	mov    BYTE PTR [edx+eax*1-0x1],cl
  521459:	84 c9                	test   cl,cl
  52145b:	75 f3                	jne    0x521450
  52145d:	6a 00                	push   0x0
  52145f:	6a 07                	push   0x7
  521461:	68 40 02 00 00       	push   0x240
  521466:	ba 4c eb 5a 00       	mov    edx,0x5aeb4c
  52146b:	b9 68 eb 5a 00       	mov    ecx,0x5aeb68
  521470:	e8 7b 6d f3 ff       	call   0x4581f0
  521475:	83 c4 0c             	add    esp,0xc

  521915:	8b d9                	mov    ebx,ecx
  521917:	57                   	push   edi
  521918:	89 9d 68 f5 ff ff    	mov    DWORD PTR [ebp-0xa98],ebx
  52191e:	e8 6d 18 04 00       	call   0x563190
  521923:	8d 75 90             	lea    esi,[ebp-0x70]
  521926:	89 85 5c f5 ff ff    	mov    DWORD PTR [ebp-0xaa4],eax
  52192c:	8b d0                	mov    edx,eax
  52192e:	2b f0                	sub    esi,eax
  521930:	8a 0a                	mov    cl,BYTE PTR [edx]
  521932:	8d 52 01             	lea    edx,[edx+0x1]
  521935:	88 4c 16 ff          	mov    BYTE PTR [esi+edx*1-0x1],cl
  521939:	84 c9                	test   cl,cl
  52193b:	75 f3                	jne    0x521930
  52193d:	ba 78 dd 58 00       	mov    edx,0x58dd78
  521942:	6a 00                	push   0x0
  521944:	81 fb 1a 01 00 00    	cmp    ebx,0x11a
  52194a:	75 09                	jne    0x521955
  52194c:	6a 0b                	push   0xb
  52194e:	b9 24 ec 5a 00       	mov    ecx,0x5aec24
  521953:	eb 07                	jmp    0x52195c
  521955:	6a 07                	push   0x7
  521957:	b9 44 ec 5a 00       	mov    ecx,0x5aec44
  52195c:	68 40 02 00 00       	push   0x240
  521961:	e8 8a 68 f3 ff       	call   0x4581f0
  521966:	8b d8                	mov    ebx,eax

  538411:	c7 05 98 97 5e 00 ff 	mov    DWORD PTR ds:0x5e9798,0xff
  538418:	00 00 00 
  53841b:	c7 05 a0 97 5e 00 0f 	mov    DWORD PTR ds:0x5e97a0,0xf
  538422:	00 00 00 
  538425:	e8 86 b5 ff ff       	call   0x5339b0
  53842a:	5f                   	pop    edi
  53842b:	5e                   	pop    esi
  53842c:	5b                   	pop    ebx
  53842d:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  538430:	33 cd                	xor    ecx,ebp
  538432:	e8 77 1c 05 00       	call   0x58a0ae
  538437:	8b e5                	mov    esp,ebp
  538439:	5d                   	pop    ebp
  53843a:	c3                   	ret
  53843b:	b9 78 18 5b 00       	mov    ecx,0x5b1878
  538440:	c7 05 84 a8 6e 00 01 	mov    DWORD PTR ds:0x6ea884,0x1
  538447:	00 00 00 
  53844a:	e8 a1 2c fd ff       	call   0x50b0f0
  53844f:	6a 00                	push   0x0
  538451:	6a 00                	push   0x0
  538453:	68 21 0d 00 00       	push   0xd21
  538458:	ba 0c 29 5b 00       	mov    edx,0x5b290c
  53845d:	b9 14 29 5b 00       	mov    ecx,0x5b2914
  538462:	e8 89 fd f1 ff       	call   0x4581f0
  538467:	83 c4 0c             	add    esp,0xc

  53b6fb:	c3                   	ret
  53b6fc:	cc                   	int3
  53b6fd:	cc                   	int3
  53b6fe:	cc                   	int3
  53b6ff:	cc                   	int3
  53b700:	55                   	push   ebp
  53b701:	8b ec                	mov    ebp,esp
  53b703:	81 ec 3c 0a 00 00    	sub    esp,0xa3c
  53b709:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  53b70e:	33 c5                	xor    eax,ebp
  53b710:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  53b713:	53                   	push   ebx
  53b714:	56                   	push   esi
  53b715:	57                   	push   edi
  53b716:	b9 78 18 5b 00       	mov    ecx,0x5b1878
  53b71b:	c7 05 84 a8 6e 00 01 	mov    DWORD PTR ds:0x6ea884,0x1
  53b722:	00 00 00 
  53b725:	e8 c6 f9 fc ff       	call   0x50b0f0
  53b72a:	6a 00                	push   0x0
  53b72c:	6a 00                	push   0x0
  53b72e:	68 30 07 00 00       	push   0x730
  53b733:	ba dc 37 5b 00       	mov    edx,0x5b37dc
  53b738:	b9 e4 37 5b 00       	mov    ecx,0x5b37e4
  53b73d:	e8 ae ca f1 ff       	call   0x4581f0
  53b742:	83 c4 0c             	add    esp,0xc

  53dd31:	8b ec                	mov    ebp,esp
  53dd33:	81 ec 6c 01 00 00    	sub    esp,0x16c
  53dd39:	c7 05 84 a8 6e 00 01 	mov    DWORD PTR ds:0x6ea884,0x1
  53dd40:	00 00 00 
  53dd43:	b9 78 18 5b 00       	mov    ecx,0x5b1878
  53dd48:	53                   	push   ebx
  53dd49:	56                   	push   esi
  53dd4a:	57                   	push   edi
  53dd4b:	e8 a0 d3 fc ff       	call   0x50b0f0
  53dd50:	8b 35 30 06 62 0a    	mov    esi,DWORD PTR ds:0xa620630
  53dd56:	8b ce                	mov    ecx,esi
  53dd58:	6a 00                	push   0x0
  53dd5a:	6a 00                	push   0x0
  53dd5c:	68 01 14 00 00       	push   0x1401
  53dd61:	68 d4 45 5b 00       	push   0x5b45d4
  53dd66:	68 e8 45 5b 00       	push   0x5b45e8
  53dd6b:	e8 50 b3 ed ff       	call   0x4190c0
  53dd70:	50                   	push   eax
  53dd71:	8b ce                	mov    ecx,esi
  53dd73:	e8 f8 b2 ed ff       	call   0x419070
  53dd78:	50                   	push   eax
  53dd79:	8b d6                	mov    edx,esi
  53dd7b:	b9 02 00 00 00       	mov    ecx,0x2
  53dd80:	e8 db 72 f1 ff       	call   0x455060
  53dd85:	83 c4 1c             	add    esp,0x1c

  565d00:	55                   	push   ebp
  565d01:	8b ec                	mov    ebp,esp
  565d03:	81 ec 74 05 00 00    	sub    esp,0x574
  565d09:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  565d0e:	33 c5                	xor    eax,ebp
  565d10:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  565d13:	8b 04 8d d0 ac 72 0a 	mov    eax,DWORD PTR [ecx*4+0xa72acd0]
  565d1a:	53                   	push   ebx
  565d1b:	56                   	push   esi
  565d1c:	89 8d f0 fb ff ff    	mov    DWORD PTR [ebp-0x410],ecx
  565d22:	b9 d4 90 5d 00       	mov    ecx,0x5d90d4
  565d27:	57                   	push   edi
  565d28:	89 85 f4 fb ff ff    	mov    DWORD PTR [ebp-0x40c],eax
  565d2e:	e8 dd 07 f9 ff       	call   0x4f6510
  565d33:	6a 00                	push   0x0
  565d35:	6a 06                	push   0x6
  565d37:	6a 40                	push   0x40
  565d39:	68 14 91 5d 00       	push   0x5d9114
  565d3e:	68 30 91 5d 00       	push   0x5d9130
  565d43:	ff 35 40 bd 72 0a    	push   DWORD PTR ds:0xa72bd40
  565d49:	83 ca ff             	or     edx,0xffffffff
  565d4c:	ff 35 9c 1c 6d 0a    	push   DWORD PTR ds:0xa6d1c9c
  565d52:	8d 4a 03             	lea    ecx,[edx+0x3]
  565d55:	e8 06 f3 ee ff       	call   0x455060
  565d5a:	8b d8                	mov    ebx,eax

  565f20:	55                   	push   ebp
  565f21:	8b ec                	mov    ebp,esp
  565f23:	81 ec 24 06 00 00    	sub    esp,0x624
  565f29:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  565f2e:	33 c5                	xor    eax,ebp
  565f30:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  565f33:	8b 04 8d d0 ac 72 0a 	mov    eax,DWORD PTR [ecx*4+0xa72acd0]
  565f3a:	53                   	push   ebx
  565f3b:	56                   	push   esi
  565f3c:	89 8d f0 fb ff ff    	mov    DWORD PTR [ebp-0x410],ecx
  565f42:	b9 1c 92 5d 00       	mov    ecx,0x5d921c
  565f47:	57                   	push   edi
  565f48:	89 85 f4 fb ff ff    	mov    DWORD PTR [ebp-0x40c],eax
  565f4e:	e8 bd 05 f9 ff       	call   0x4f6510
  565f53:	6a 00                	push   0x0
  565f55:	6a 01                	push   0x1
  565f57:	6a 40                	push   0x40
  565f59:	68 54 92 5d 00       	push   0x5d9254
  565f5e:	68 74 92 5d 00       	push   0x5d9274
  565f63:	ff 35 40 bd 72 0a    	push   DWORD PTR ds:0xa72bd40
  565f69:	83 ca ff             	or     edx,0xffffffff
  565f6c:	ff 35 9c 1c 6d 0a    	push   DWORD PTR ds:0xa6d1c9c
  565f72:	8d 4a 03             	lea    ecx,[edx+0x3]
  565f75:	e8 e6 f0 ee ff       	call   0x455060
  565f7a:	8b d8                	mov    ebx,eax

  57bd7c:	0f b7 06             	movzx  eax,WORD PTR [esi]
  57bd7f:	3b 05 40 bd 72 0a    	cmp    eax,DWORD PTR ds:0xa72bd40
  57bd85:	75 2e                	jne    0x57bdb5
  57bd87:	0f b7 46 06          	movzx  eax,WORD PTR [esi+0x6]
  57bd8b:	50                   	push   eax
  57bd8c:	ff 76 0a             	push   DWORD PTR [esi+0xa]
  57bd8f:	0f b6 46 02          	movzx  eax,BYTE PTR [esi+0x2]
  57bd93:	50                   	push   eax
  57bd94:	8d 84 24 34 0b 02 00 	lea    eax,[esp+0x20b34]
  57bd9b:	68 40 be 5d 00       	push   0x5dbe40
  57bda0:	50                   	push   eax
  57bda1:	e8 2a 53 e8 ff       	call   0x4010d0
  57bda6:	83 c4 14             	add    esp,0x14
  57bda9:	8d 8c 24 28 0b 02 00 	lea    ecx,[esp+0x20b28]
  57bdb0:	e8 5b a7 f7 ff       	call   0x4f6510
  57bdb5:	83 c6 24             	add    esi,0x24
  57bdb8:	81 fe ea a6 72 0a    	cmp    esi,0xa72a6ea
  57bdbe:	7c b0                	jl     0x57bd70
  57bdc0:	6a 00                	push   0x0
  57bdc2:	6a 00                	push   0x0
  57bdc4:	6a 00                	push   0x0
  57bdc6:	ba 16 c6 58 00       	mov    edx,0x58c616
  57bdcb:	b9 50 be 5d 00       	mov    ecx,0x5dbe50
  57bdd0:	e8 1b c4 ed ff       	call   0x4581f0
  57bdd5:	83 c4 0c             	add    esp,0xc

  57bdff:	8d 94 24 28 0b 02 00 	lea    edx,[esp+0x20b28]
  57be06:	2b d0                	sub    edx,eax
  57be08:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [eax+eax*1+0x0]
  57be0f:	00 
  57be10:	8a 08                	mov    cl,BYTE PTR [eax]
  57be12:	8d 40 01             	lea    eax,[eax+0x1]
  57be15:	88 4c 02 ff          	mov    BYTE PTR [edx+eax*1-0x1],cl
  57be19:	84 c9                	test   cl,cl
  57be1b:	75 f3                	jne    0x57be10
  57be1d:	8d 84 24 28 0b 02 00 	lea    eax,[esp+0x20b28]
  57be24:	6a 00                	push   0x0
  57be26:	50                   	push   eax
  57be27:	ff d6                	call   esi
  57be29:	83 c4 04             	add    esp,0x4
  57be2c:	b9 0b 00 00 00       	mov    ecx,0xb
  57be31:	e9 24 87 ff ff       	jmp    0x57455a
  57be36:	83 f9 67             	cmp    ecx,0x67
  57be39:	0f 85 d1 00 00 00    	jne    0x57bf10
  57be3f:	6a 00                	push   0x0
  57be41:	6a 00                	push   0x0
  57be43:	6a 00                	push   0x0
  57be45:	ba 16 c6 58 00       	mov    edx,0x58c616
  57be4a:	b9 50 be 5d 00       	mov    ecx,0x5dbe50
  57be4f:	e8 9c c3 ed ff       	call   0x4581f0
  57be54:	83 c4 0c             	add    esp,0xc

  57be31:	e9 24 87 ff ff       	jmp    0x57455a
  57be36:	83 f9 67             	cmp    ecx,0x67
  57be39:	0f 85 d1 00 00 00    	jne    0x57bf10
  57be3f:	6a 00                	push   0x0
  57be41:	6a 00                	push   0x0
  57be43:	6a 00                	push   0x0
  57be45:	ba 16 c6 58 00       	mov    edx,0x58c616
  57be4a:	b9 50 be 5d 00       	mov    ecx,0x5dbe50
  57be4f:	e8 9c c3 ed ff       	call   0x4581f0
  57be54:	83 c4 0c             	add    esp,0xc
  57be57:	85 c0                	test   eax,eax
  57be59:	0f 88 60 0b 00 00    	js     0x57c9bf
  57be5f:	8b 0c 85 d0 ac 72 0a 	mov    ecx,DWORD PTR [eax*4+0xa72acd0]
  57be66:	e8 a5 42 f4 ff       	call   0x4c0110
  57be6b:	6a 00                	push   0x0
  57be6d:	b9 2b 00 00 00       	mov    ecx,0x2b
  57be72:	8d bc 24 0c a1 00 00 	lea    edi,[esp+0xa10c]
  57be79:	be 58 52 91 05       	mov    esi,0x5915258
  57be7e:	ba 16 c6 58 00       	mov    edx,0x58c616
  57be83:	f3 a5                	rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
  57be85:	6a 00                	push   0x0
  57be87:	6a 00                	push   0x0
  57be89:	b9 50 be 5d 00       	mov    ecx,0x5dbe50
  57be8e:	e8 5d c3 ed ff       	call   0x4581f0
  57be93:	83 c4 0c             	add    esp,0xc

  57bf17:	b9 0c 2a 5a 00       	mov    ecx,0x5a2a0c
  57bf1c:	e8 1f 37 f4 ff       	call   0x4bf640
  57bf21:	8d 8c 24 e8 0b 00 00 	lea    ecx,[esp+0xbe8]
  57bf28:	51                   	push   ecx
  57bf29:	8b c8                	mov    ecx,eax
  57bf2b:	e8 60 42 f4 ff       	call   0x4c0190
  57bf30:	8b f0                	mov    esi,eax
  57bf32:	b9 2b 00 00 00       	mov    ecx,0x2b
  57bf37:	bf 58 52 91 05       	mov    edi,0x5915258
  57bf3c:	83 c4 04             	add    esp,0x4
  57bf3f:	f3 a5                	rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
  57bf41:	ba 58 52 91 05       	mov    edx,0x5915258
  57bf46:	b9 70 be 5d 00       	mov    ecx,0x5dbe70
  57bf4b:	e8 f0 5f f3 ff       	call   0x4b1f40
  57bf50:	be 58 52 91 05       	mov    esi,0x5915258
  57bf55:	e9 df 85 ff ff       	jmp    0x574539
  57bf5a:	83 f9 37             	cmp    ecx,0x37
  57bf5d:	0f 85 2f 08 00 00    	jne    0x57c792
  57bf63:	6a 00                	push   0x0
  57bf65:	6a 00                	push   0x0
  57bf67:	6a 00                	push   0x0
  57bf69:	ba 16 c6 58 00       	mov    edx,0x58c616
  57bf6e:	b9 50 be 5d 00       	mov    ecx,0x5dbe50
  57bf73:	e8 78 c2 ed ff       	call   0x4581f0
  57bf78:	8b f0                	mov    esi,eax

  57c759:	8d 84 24 50 03 00 00 	lea    eax,[esp+0x350]
  57c760:	b9 58 52 91 05       	mov    ecx,0x5915258
  57c765:	50                   	push   eax
  57c766:	e8 45 6f eb ff       	call   0x4336b0
  57c76b:	83 c4 04             	add    esp,0x4
  57c76e:	bf 01 00 00 00       	mov    edi,0x1
  57c773:	83 7c 24 2c 00       	cmp    DWORD PTR [esp+0x2c],0x0
  57c778:	0f 8d e5 f7 ff ff    	jge    0x57bf63
  57c77e:	5f                   	pop    edi
  57c77f:	5e                   	pop    esi
  57c780:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  57c787:	33 cc                	xor    ecx,esp
  57c789:	e8 20 d9 00 00       	call   0x58a0ae
  57c78e:	8b e5                	mov    esp,ebp
  57c790:	5d                   	pop    ebp
  57c791:	c3                   	ret
  57c792:	83 f9 71             	cmp    ecx,0x71
  57c795:	0f 85 e1 01 00 00    	jne    0x57c97c
  57c79b:	6a 00                	push   0x0
  57c79d:	6a 00                	push   0x0
  57c79f:	6a 00                	push   0x0
  57c7a1:	ba 64 c1 5d 00       	mov    edx,0x5dc164
  57c7a6:	b9 50 be 5d 00       	mov    ecx,0x5dbe50
  57c7ab:	e8 40 ba ed ff       	call   0x4581f0
  57c7b0:	83 c4 0c             	add    esp,0xc

  4ab609:	8b cb                	mov    ecx,ebx
  4ab60b:	e8 30 ec ff ff       	call   0x4aa240
  4ab610:	85 c0                	test   eax,eax
  4ab612:	0f 84 87 01 00 00    	je     0x4ab79f
  4ab618:	b9 64 01 5a 00       	mov    ecx,0x5a0164
  4ab61d:	89 1d 4c 2a 62 0a    	mov    DWORD PTR ds:0xa622a4c,ebx
  4ab623:	e8 d8 64 0b 00       	call   0x561b00
  4ab628:	8b c8                	mov    ecx,eax
  4ab62a:	e8 e1 ae 04 00       	call   0x4f6510
  4ab62f:	68 58 02 00 00       	push   0x258
  4ab634:	6a 00                	push   0x0
  4ab636:	68 01 40 00 00       	push   0x4001
  4ab63b:	68 98 01 5a 00       	push   0x5a0198
  4ab640:	68 a0 01 5a 00       	push   0x5a01a0
  4ab645:	e9 4a ff ff ff       	jmp    0x4ab594

  52036d:	83 c4 0c             	add    esp,0xc
  520370:	83 7c 24 30 00       	cmp    DWORD PTR [esp+0x30],0x0
  520375:	0f 85 b1 03 00 00    	jne    0x52072c
  52037b:	6a 00                	push   0x0
  52037d:	81 ff 18 01 00 00    	cmp    edi,0x118
  520383:	75 0e                	jne    0x520393
  520385:	6a 0b                	push   0xb
  520387:	ba 60 e6 5a 00       	mov    edx,0x5ae660
  52038c:	b9 68 e6 5a 00       	mov    ecx,0x5ae668
  520391:	eb 0c                	jmp    0x52039f
  520393:	6a 06                	push   0x6
  520395:	ba 90 e6 5a 00       	mov    edx,0x5ae690
  52039a:	b9 a0 e6 5a 00       	mov    ecx,0x5ae6a0
  52039f:	6a 60                	push   0x60
  5203a1:	e8 4a 7e f3 ff       	call   0x4581f0

  52193d:	ba 78 dd 58 00       	mov    edx,0x58dd78
  521942:	6a 00                	push   0x0
  521944:	81 fb 1a 01 00 00    	cmp    ebx,0x11a
  52194a:	75 09                	jne    0x521955
  52194c:	6a 0b                	push   0xb
  52194e:	b9 24 ec 5a 00       	mov    ecx,0x5aec24
  521953:	eb 07                	jmp    0x52195c
  521955:	6a 07                	push   0x7
  521957:	b9 44 ec 5a 00       	mov    ecx,0x5aec44
  52195c:	68 40 02 00 00       	push   0x240
  521961:	e8 8a 68 f3 ff       	call   0x4581f0

  455060:	55                   	push   ebp
  455061:	8b ec                	mov    ebp,esp
  455063:	83 e4 f8             	and    esp,0xfffffff8
  455066:	b8 c4 14 00 00       	mov    eax,0x14c4
  45506b:	e8 60 60 13 00       	call   0x58b0d0
  455070:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  455075:	33 c4                	xor    eax,esp
  455077:	89 84 24 c0 14 00 00 	mov    DWORD PTR [esp+0x14c0],eax
  45507e:	8b 45 14             	mov    eax,DWORD PTR [ebp+0x14]
  455081:	53                   	push   ebx
  455082:	56                   	push   esi
  455083:	57                   	push   edi
  455084:	33 db                	xor    ebx,ebx
  455086:	89 44 24 48          	mov    DWORD PTR [esp+0x48],eax
  45508a:	32 c0                	xor    al,al

  4555f8:	8b 75 10             	mov    esi,DWORD PTR [ebp+0x10]
  4555fb:	8b ce                	mov    ecx,esi
  4555fd:	8d 51 01             	lea    edx,[ecx+0x1]
  455600:	8a 01                	mov    al,BYTE PTR [ecx]
  455602:	41                   	inc    ecx
  455603:	84 c0                	test   al,al
  455605:	75 f9                	jne    0x455600
  455607:	2b ca                	sub    ecx,edx
  455609:	74 1a                	je     0x455625
  45560b:	8d 94 24 98 07 00 00 	lea    edx,[esp+0x798]
  455612:	8b ce                	mov    ecx,esi
  455614:	2b d6                	sub    edx,esi
  455616:	8a 01                	mov    al,BYTE PTR [ecx]
  455618:	8d 49 01             	lea    ecx,[ecx+0x1]
  45561b:	88 44 0a ff          	mov    BYTE PTR [edx+ecx*1-0x1],al
  45561f:	84 c0                	test   al,al
  455621:	75 f3                	jne    0x455616
  455623:	eb 0f                	jmp    0x455634
  455625:	0f 10 05 08 5b 59 00 	movups xmm0,XMMWORD PTR ds:0x595b08
  45562c:	0f 11 84 24 98 07 00 	movups XMMWORD PTR [esp+0x798],xmm0
  455633:	00 
  455634:	8b 15 f0 2b 5e 00    	mov    edx,DWORD PTR ds:0x5e2bf0
  45563a:	8d 84 24 98 07 00 00 	lea    eax,[esp+0x798]
  455641:	8b 0d e0 23 5e 00    	mov    ecx,DWORD PTR ds:0x5e23e0
  455647:	6a 00                	push   0x0
  455649:	68 82 00 00 00       	push   0x82
  45564e:	50                   	push   eax
  45564f:	ff 35 ec 23 5e 00    	push   DWORD PTR ds:0x5e23ec
  455655:	ff 35 f4 2b 5e 00    	push   DWORD PTR ds:0x5e2bf4
  45565b:	e8 10 0c 0c 00       	call   0x516270
  455660:	8b 0d e0 23 5e 00    	mov    ecx,DWORD PTR ds:0x5e23e0
  455666:	83 c4 14             	add    esp,0x14
  455669:	a1 f4 2b 5e 00       	mov    eax,ds:0x5e2bf4
  45566e:	8b 15 ec 49 78 0a    	mov    edx,DWORD PTR ds:0xa7849ec
  455674:	83 c0 f6             	add    eax,0xfffffff6
  455677:	6a 00                	push   0x0
  455679:	6a 10                	push   0x10
  45567b:	68 16 c6 58 00       	push   0x58c616
  455680:	6a 64                	push   0x64
  455682:	50                   	push   eax
  455683:	8d 49 05             	lea    ecx,[ecx+0x5]
  455686:	e8 e5 0b 0c 00       	call   0x516270
  45568b:	8b 74 24 54          	mov    esi,DWORD PTR [esp+0x54]
  45568f:	83 c4 14             	add    esp,0x14
  455692:	85 f6                	test   esi,esi
  455694:	74 15                	je     0x4556ab
  455696:	a0 28 5b 59 00       	mov    al,ds:0x595b28
  45569b:	0f 10 05 18 5b 59 00 	movups xmm0,XMMWORD PTR ds:0x595b18
  4556a2:	88 84 24 a8 07 00 00 	mov    BYTE PTR [esp+0x7a8],al
  4556a9:	eb 21                	jmp    0x4556cc
  4556ab:	66 a1 3c 5b 59 00    	mov    ax,ds:0x595b3c
  4556b1:	0f 10 05 2c 5b 59 00 	movups xmm0,XMMWORD PTR ds:0x595b2c
  4556b8:	66 89 84 24 a8 07 00 	mov    WORD PTR [esp+0x7a8],ax
  4556bf:	00 
  4556c0:	a0 3e 5b 59 00       	mov    al,ds:0x595b3e
  4556c5:	88 84 24 aa 07 00 00 	mov    BYTE PTR [esp+0x7aa],al
  4556cc:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4556d1:	68 de 00 00 00       	push   0xde
  4556d6:	68 c4 00 00 00       	push   0xc4
  4556db:	0f 11 84 24 a0 07 00 	movups XMMWORD PTR [esp+0x7a0],xmm0
  4556e2:	00 
  4556e3:	68 b0 00 00 00       	push   0xb0
  4556e8:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4556eb:	ff d3                	call   ebx
  4556ed:	8b 15 ec 49 78 0a    	mov    edx,DWORD PTR ds:0xa7849ec
  4556f3:	8b 0d e0 23 5e 00    	mov    ecx,DWORD PTR ds:0x5e23e0
  4556f9:	6a 00                	push   0x0
  4556fb:	50                   	push   eax
  4556fc:	8d 84 24 b0 07 00 00 	lea    eax,[esp+0x7b0]
  455703:	50                   	push   eax
  455704:	8d 52 05             	lea    edx,[edx+0x5]
  455707:	8d 49 0d             	lea    ecx,[ecx+0xd]
  45570a:	e8 91 8e 0b 00       	call   0x50e5a0
  45570f:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  455714:	83 c4 1c             	add    esp,0x1c
  455717:	6a 00                	push   0x0
  455719:	68 8c 00 00 00       	push   0x8c
  45571e:	68 e6 00 00 00       	push   0xe6
  455723:	68 f0 00 00 00       	push   0xf0
  455728:	ff 70 04             	push   DWORD PTR [eax+0x4]
  45572b:	ff d3                	call   ebx
  45572d:	83 c4 10             	add    esp,0x10
  455730:	83 ca ff             	or     edx,0xffffffff
  455733:	0b ca                	or     ecx,edx
  455735:	50                   	push   eax
  455736:	ff 74 24 50          	push   DWORD PTR [esp+0x50]
  45573a:	e8 61 8e 0b 00       	call   0x50e5a0
  45573f:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  455744:	83 c4 0c             	add    esp,0xc
  455747:	6a 00                	push   0x0
  455749:	68 de 00 00 00       	push   0xde
  45574e:	68 c4 00 00 00       	push   0xc4
  455753:	68 b0 00 00 00       	push   0xb0
  455758:	ff 70 04             	push   DWORD PTR [eax+0x4]
  45575b:	ff d3                	call   ebx
  45575d:	83 c4 10             	add    esp,0x10
  455760:	83 ca ff             	or     edx,0xffffffff
  455763:	0b ca                	or     ecx,edx
  455765:	50                   	push   eax
  455766:	68 5c 28 59 00       	push   0x59285c
  45576b:	e8 30 8e 0b 00       	call   0x50e5a0

  45477a:	8b 8d ec f7 ff ff    	mov    ecx,DWORD PTR [ebp-0x814]
  454780:	8b d3                	mov    edx,ebx
  454782:	6a 00                	push   0x0
  454784:	6a 00                	push   0x0
  454786:	68 14 79 59 00       	push   0x597914
  45478b:	e8 10 9e 0b 00       	call   0x50e5a0
  454790:	83 c4 0c             	add    esp,0xc
  454793:	eb 24                	jmp    0x4547b9
  454795:	f3 0f 5e c1          	divss  xmm0,xmm1
  454799:	8b 8d ec f7 ff ff    	mov    ecx,DWORD PTR [ebp-0x814]
  45479f:	8d 53 fe             	lea    edx,[ebx-0x2]
  4547a2:	f3 0f 59 05 08 d6 5d 	mulss  xmm0,DWORD PTR ds:0x5dd608
  4547a9:	00 
  4547aa:	f3 0f 2c c0          	cvttss2si eax,xmm0
  4547ae:	50                   	push   eax
  4547af:	6a 1e                	push   0x1e
  4547b1:	e8 ba 89 0b 00       	call   0x50d170
  4547b6:	83 c4 08             	add    esp,0x8
  4547b9:	8b 8d e4 f7 ff ff    	mov    ecx,DWORD PTR [ebp-0x81c]
  4547bf:	6a 00                	push   0x0
  4547c1:	ff b5 c4 f7 ff ff    	push   DWORD PTR [ebp-0x83c]
  4547c7:	8b 91 b4 ed 6e 00    	mov    edx,DWORD PTR [ecx+0x6eedb4]
  4547cd:	8b 89 b0 ed 6e 00    	mov    ecx,DWORD PTR [ecx+0x6eedb0]
  4547d3:	e8 b8 73 ff ff       	call   0x44bb90
  4547d8:	8b 8d d8 f7 ff ff    	mov    ecx,DWORD PTR [ebp-0x828]
  4547de:	8b d3                	mov    edx,ebx
  4547e0:	50                   	push   eax
  4547e1:	e8 ba 9d 0b 00       	call   0x50e5a0

  44b17e:	f6 85 42 ff ff ff 80 	test   BYTE PTR [ebp-0xbe],0x80
  44b185:	8d 4e 14             	lea    ecx,[esi+0x14]
  44b188:	6a 00                	push   0x0
  44b18a:	8b d3                	mov    edx,ebx
  44b18c:	6a 00                	push   0x0
  44b18e:	74 07                	je     0x44b197
  44b190:	68 00 85 59 00       	push   0x598500
  44b195:	eb 05                	jmp    0x44b19c
  44b197:	68 04 85 59 00       	push   0x598504
  44b19c:	e8 ff 33 0c 00       	call   0x50e5a0
  44b1a1:	83 c4 0c             	add    esp,0xc

  44bd0b:	33 c9                	xor    ecx,ecx
  44bd0d:	0f 28 c2             	movaps xmm0,xmm2
  44bd10:	e8 db f5 ff ff       	call   0x44b2f0
  44bd15:	8b d3                	mov    edx,ebx
  44bd17:	2b d0                	sub    edx,eax
  44bd19:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [eax+0x0]
  44bd20:	8a 08                	mov    cl,BYTE PTR [eax]
  44bd22:	8d 40 01             	lea    eax,[eax+0x1]
  44bd25:	88 4c 02 ff          	mov    BYTE PTR [edx+eax*1-0x1],cl
  44bd29:	84 c9                	test   cl,cl
  44bd2b:	75 f3                	jne    0x44bd20
  44bd2d:	5f                   	pop    edi
  44bd2e:	5e                   	pop    esi
  44bd2f:	8b c3                	mov    eax,ebx
  44bd31:	5b                   	pop    ebx
  44bd32:	8b e5                	mov    esp,ebp

  456861:	f7 45 18 00 04 00 00 	test   DWORD PTR [ebp+0x18],0x400
  456868:	0f 85 ff 0c 00 00    	jne    0x45756d
  45686e:	80 7c 24 2c 00       	cmp    BYTE PTR [esp+0x2c],0x0
  456873:	75 0a                	jne    0x45687f
  456875:	b9 34 5d 59 00       	mov    ecx,0x595d34
  45687a:	e8 91 fc 09 00       	call   0x4f6510
  45687f:	33 c9                	xor    ecx,ecx
  456881:	8a 81 34 5d 59 00    	mov    al,BYTE PTR [ecx+0x595d34]
  456887:	8d 49 01             	lea    ecx,[ecx+0x1]
  45688a:	88 81 2f 2c 6f 00    	mov    BYTE PTR [ecx+0x6f2c2f],al
  456890:	84 c0                	test   al,al
  456892:	75 ed                	jne    0x456881
  456894:	6a 21                	push   0x21
  456896:	68 d8 5a 59 00       	push   0x595ad8
  45689b:	ff 15 48 c3 58 00    	call   DWORD PTR ds:0x58c348
  4568a1:	83 c4 08             	add    esp,0x8
  4568a4:	85 c0                	test   eax,eax
  4568a6:	74 1b                	je     0x4568c3
  4568a8:	33 c9                	xor    ecx,ecx
  4568aa:	66 0f 1f 44 00 00    	nop    WORD PTR [eax+eax*1+0x0]
  4568b0:	8a 81 35 5d 59 00    	mov    al,BYTE PTR [ecx+0x595d35]
  4568b6:	8d 49 01             	lea    ecx,[ecx+0x1]
  4568b9:	88 81 2f 2c 6f 00    	mov    BYTE PTR [ecx+0x6f2c2f],al
  4568bf:	84 c0                	test   al,al
  4568c1:	75 ed                	jne    0x4568b0
  4568c3:	b9 54 5d 59 00       	mov    ecx,0x595d54
  4568c8:	e8 43 52 0a 00       	call   0x4fbb10
  4568cd:	84 c0                	test   al,al

  4fbde3:	50                   	push   eax
  4fbde4:	89 74 24 1c          	mov    DWORD PTR [esp+0x1c],esi
  4fbde8:	e8 e3 52 f0 ff       	call   0x4010d0
  4fbded:	83 c4 0c             	add    esp,0xc
  4fbdf0:	85 ff                	test   edi,edi
  4fbdf2:	74 0f                	je     0x4fbe03
  4fbdf4:	53                   	push   ebx
  4fbdf5:	8d 44 24 24          	lea    eax,[esp+0x24]
  4fbdf9:	57                   	push   edi
  4fbdfa:	50                   	push   eax
  4fbdfb:	e8 d0 52 f0 ff       	call   0x4010d0
  4fbe00:	83 c4 0c             	add    esp,0xc
  4fbe03:	8b 7d 08             	mov    edi,DWORD PTR [ebp+0x8]
  4fbe06:	8d 44 24 20          	lea    eax,[esp+0x20]
  4fbe0a:	8b 55 0c             	mov    edx,DWORD PTR [ebp+0xc]
  4fbe0d:	8b cf                	mov    ecx,edi
  4fbe0f:	6a 00                	push   0x0
  4fbe11:	6a 08                	push   0x8
  4fbe13:	50                   	push   eax
  4fbe14:	6a 37                	push   0x37
  4fbe16:	68 27 01 00 00       	push   0x127
  4fbe1b:	e8 50 a4 01 00       	call   0x516270
  4fbe20:	8b 45 0c             	mov    eax,DWORD PTR [ebp+0xc]

  4fbf87:	ff 24 85 18 c1 4f 00 	jmp    DWORD PTR [eax*4+0x4fc118]
  4fbf8e:	53                   	push   ebx
  4fbf8f:	8d 44 24 24          	lea    eax,[esp+0x24]
  4fbf93:	68 10 a7 5a 00       	push   0x5aa710
  4fbf98:	50                   	push   eax
  4fbf99:	e8 32 51 f0 ff       	call   0x4010d0
  4fbf9e:	8b 5d 0c             	mov    ebx,DWORD PTR [ebp+0xc]
  4fbfa1:	8d 44 24 2c          	lea    eax,[esp+0x2c]
  4fbfa5:	83 c4 0c             	add    esp,0xc
  4fbfa8:	8b d3                	mov    edx,ebx
  4fbfaa:	8b cf                	mov    ecx,edi
  4fbfac:	6a 00                	push   0x0
  4fbfae:	6a 08                	push   0x8
  4fbfb0:	50                   	push   eax
  4fbfb1:	6a 37                	push   0x37
  4fbfb3:	68 27 01 00 00       	push   0x127
  4fbfb8:	e8 b3 a2 01 00       	call   0x516270

  4fc034:	6a 01                	push   0x1
  4fc036:	68 ff 00 00 00       	push   0xff
  4fc03b:	68 ff 00 00 00       	push   0xff
  4fc040:	68 ff 00 00 00       	push   0xff
  4fc045:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fc048:	ff d6                	call   esi
  4fc04a:	8b 55 0c             	mov    edx,DWORD PTR [ebp+0xc]
  4fc04d:	83 c4 10             	add    esp,0x10
  4fc050:	8b 4d 08             	mov    ecx,DWORD PTR [ebp+0x8]
  4fc053:	83 c1 0a             	add    ecx,0xa
  4fc056:	50                   	push   eax
  4fc057:	68 44 a7 5a 00       	push   0x5aa744
  4fc05c:	8d 52 1f             	lea    edx,[edx+0x1f]
  4fc05f:	e8 3c 25 01 00       	call   0x50e5a0
  4fc064:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4fc069:	83 c4 0c             	add    esp,0xc
  4fc06c:	68 de 00 00 00       	push   0xde
  4fc071:	68 c4 00 00 00       	push   0xc4
  4fc076:	68 b0 00 00 00       	push   0xb0
  4fc07b:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fc07e:	ff d6                	call   esi
  4fc080:	83 c4 10             	add    esp,0x10
  4fc083:	ba 0a 00 00 00       	mov    edx,0xa
  4fc088:	8b c8                	mov    ecx,eax
  4fc08a:	e8 21 35 01 00       	call   0x50f5b0

  4fbb97:	56                   	push   esi
  4fbb98:	8d 45 90             	lea    eax,[ebp-0x70]
  4fbb9b:	68 70 c6 58 00       	push   0x58c670
  4fbba0:	50                   	push   eax
  4fbba1:	e8 2a 55 f0 ff       	call   0x4010d0
  4fbba6:	0f 28 05 c0 da 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5ddac0
  4fbbad:	8d 45 80             	lea    eax,[ebp-0x80]
  4fbbb0:	83 c4 0c             	add    esp,0xc
  4fbbb3:	0f 11 45 80          	movups XMMWORD PTR [ebp-0x80],xmm0
  4fbbb7:	50                   	push   eax
  4fbbb8:	ff 35 14 20 5c 0a    	push   DWORD PTR ds:0xa5c2014
  4fbbbe:	50                   	push   eax
  4fbbbf:	ff 35 10 bb 5b 06    	push   DWORD PTR ds:0x65bbb10
  4fbbc5:	ff 15 04 c2 58 00    	call   DWORD PTR ds:0x58c204
  4fbbcb:	6a 00                	push   0x0
  4fbbcd:	6a 08                	push   0x8
  4fbbcf:	8d 45 90             	lea    eax,[ebp-0x70]
  4fbbd2:	ba 1f 02 00 00       	mov    edx,0x21f
  4fbbd7:	50                   	push   eax
  4fbbd8:	6a 37                	push   0x37
  4fbbda:	68 27 01 00 00       	push   0x127
  4fbbdf:	8d 4a d5             	lea    ecx,[edx-0x2b]
  4fbbe2:	e8 89 a6 01 00       	call   0x516270
  4fbbe7:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10

  4fbc36:	ba 0d 02 00 00       	mov    edx,0x20d
  4fbc3b:	c7 05 a0 4a 35 06 01 	mov    DWORD PTR ds:0x6354aa0,0x1
  4fbc42:	00 00 00 
  4fbc45:	b9 59 00 00 00       	mov    ecx,0x59
  4fbc4a:	68 64 f8 58 00       	push   0x58f864
  4fbc4f:	68 3a 02 00 00       	push   0x23a
  4fbc54:	e8 97 3e fd ff       	call   0x4cfaf0
  4fbc59:	68 6c f8 58 00       	push   0x58f86c
  4fbc5e:	68 3a 02 00 00       	push   0x23a
  4fbc63:	ba 49 02 00 00       	mov    edx,0x249
  4fbc68:	b9 4e 00 00 00       	mov    ecx,0x4e
  4fbc6d:	e8 7e 3e fd ff       	call   0x4cfaf0
  4fbc72:	83 c4 10             	add    esp,0x10

  5146a1:	8d 43 01             	lea    eax,[ebx+0x1]
  5146a4:	89 bd 64 ff ff ff    	mov    DWORD PTR [ebp-0x9c],edi
  5146aa:	6a 2e                	push   0x2e
  5146ac:	50                   	push   eax
  5146ad:	89 9d 5c ff ff ff    	mov    DWORD PTR [ebp-0xa4],ebx
  5146b3:	ff 15 48 c3 58 00    	call   DWORD PTR ds:0x58c348
  5146b9:	83 c4 08             	add    esp,0x8
  5146bc:	89 85 58 ff ff ff    	mov    DWORD PTR [ebp-0xa8],eax
  5146c2:	85 c0                	test   eax,eax
  5146c4:	74 06                	je     0x5146cc
  5146c6:	8b f0                	mov    esi,eax
  5146c8:	2b f3                	sub    esi,ebx
  5146ca:	eb 0e                	jmp    0x5146da
  5146cc:	8b f3                	mov    esi,ebx
  5146ce:	8d 4e 01             	lea    ecx,[esi+0x1]
  5146d1:	8a 06                	mov    al,BYTE PTR [esi]
  5146d3:	46                   	inc    esi
  5146d4:	84 c0                	test   al,al
  5146d6:	75 f9                	jne    0x5146d1
  5146d8:	2b f1                	sub    esi,ecx
  5146da:	6a 3c                	push   0x3c
  5146dc:	53                   	push   ebx
  5146dd:	89 b5 68 ff ff ff    	mov    DWORD PTR [ebp-0x98],esi
  5146e3:	ff 15 48 c3 58 00    	call   DWORD PTR ds:0x58c348
  5146e9:	83 c4 08             	add    esp,0x8
  5146ec:	85 c0                	test   eax,eax
  5146ee:	74 19                	je     0x514709
  5146f0:	6a 3e                	push   0x3e
  5146f2:	53                   	push   ebx
  5146f3:	ff 15 48 c3 58 00    	call   DWORD PTR ds:0x58c348
  5146f9:	83 c4 08             	add    esp,0x8
  5146fc:	85 c0                	test   eax,eax
  5146fe:	74 09                	je     0x514709
  514700:	83 ee 02             	sub    esi,0x2
  514703:	89 b5 68 ff ff ff    	mov    DWORD PTR [ebp-0x98],esi
  514709:	0f 28 05 d0 d8 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5dd8d0

  514863:	8a 04 1a             	mov    al,BYTE PTR [edx+ebx*1]
  514866:	3c 2e                	cmp    al,0x2e
  514868:	75 08                	jne    0x514872
  51486a:	85 db                	test   ebx,ebx
  51486c:	0f 85 67 01 00 00    	jne    0x5149d9
  514872:	3c 3c                	cmp    al,0x3c
  514874:	75 31                	jne    0x5148a7
  514876:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  51487b:	bf 01 00 00 00       	mov    edi,0x1
  514880:	68 8c 00 00 00       	push   0x8c
  514885:	68 e6 00 00 00       	push   0xe6
  51488a:	68 f0 00 00 00       	push   0xf0
  51488f:	ff 70 04             	push   DWORD PTR [eax+0x4]
  514892:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  514898:	8b 95 5c ff ff ff    	mov    edx,DWORD PTR [ebp-0xa4]
  51489e:	83 c4 10             	add    esp,0x10
  5148a1:	89 85 68 ff ff ff    	mov    DWORD PTR [ebp-0x98],eax
  5148a7:	8a 0c 1a             	mov    cl,BYTE PTR [edx+ebx*1]
  5148aa:	80 f9 3e             	cmp    cl,0x3e
  5148ad:	75 0c                	jne    0x5148bb
  5148af:	c7 85 68 ff ff ff 00 	mov    DWORD PTR [ebp-0x98],0x0
  5148b6:	00 00 00 
  5148b9:	33 ff                	xor    edi,edi
  5148bb:	0f b6 c1             	movzx  eax,cl
  5148be:	50                   	push   eax
  5148bf:	68 30 ae 5a 00       	push   0x5aae30
  5148c4:	ff 15 48 c3 58 00    	call   DWORD PTR ds:0x58c348
  5148ca:	83 c4 08             	add    esp,0x8
  5148cd:	85 c0                	test   eax,eax
  5148cf:	0f 85 b5 00 00 00    	jne    0x51498a
  5148d5:	8b 85 5c ff ff ff    	mov    eax,DWORD PTR [ebp-0xa4]
  5148db:	0f b6 04 18          	movzx  eax,BYTE PTR [eax+ebx*1]
  5148df:	50                   	push   eax
  5148e0:	8d 45 8c             	lea    eax,[ebp-0x74]
  5148e3:	68 dc d6 58 00       	push   0x58d6dc
  5148e8:	50                   	push   eax
  5148e9:	e8 e2 c7 ee ff       	call   0x4010d0
  5148ee:	83 c4 0c             	add    esp,0xc
  5148f1:	83 ff 02             	cmp    edi,0x2
  5148f4:	0f 85 bd 00 00 00    	jne    0x5149b7
  5148fa:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  5148ff:	6a 00                	push   0x0
  514901:	68 ff 00 00 00       	push   0xff
  514906:	68 ff 00 00 00       	push   0xff
  51490b:	68 ff 00 00 00       	push   0xff
  514910:	ff 70 04             	push   DWORD PTR [eax+0x4]
  514913:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  514919:	8b 95 64 ff ff ff    	mov    edx,DWORD PTR [ebp-0x9c]
  51491f:	8d 4e ff             	lea    ecx,[esi-0x1]
  514922:	83 c4 10             	add    esp,0x10
  514925:	8d 52 05             	lea    edx,[edx+0x5]
  514928:	50                   	push   eax
  514929:	8d 45 8c             	lea    eax,[ebp-0x74]
  51492c:	50                   	push   eax
  51492d:	e8 6e 9c ff ff       	call   0x50e5a0
  514932:	83 c4 0c             	add    esp,0xc
  514935:	c7 05 68 10 61 0a 00 	mov    DWORD PTR ds:0xa611068,0x0
  51493c:	00 00 00 
  51493f:	8b 95 64 ff ff ff    	mov    edx,DWORD PTR [ebp-0x9c]
  514945:	8d 45 8c             	lea    eax,[ebp-0x74]
  514948:	6a 00                	push   0x0
  51494a:	ff b5 68 ff ff ff    	push   DWORD PTR [ebp-0x98]
  514950:	8b ce                	mov    ecx,esi
  514952:	50                   	push   eax
  514953:	8d 52 05             	lea    edx,[edx+0x5]
  514956:	e8 45 9c ff ff       	call   0x50e5a0
  51495b:	83 c4 0c             	add    esp,0xc
  51495e:	83 ff 02             	cmp    edi,0x2
  514961:	75 24                	jne    0x514987
  514963:	8b 95 64 ff ff ff    	mov    edx,DWORD PTR [ebp-0x9c]
  514969:	8d 46 07             	lea    eax,[esi+0x7]
  51496c:	83 c2 0d             	add    edx,0xd
  51496f:	c7 05 68 10 61 0a 00 	mov    DWORD PTR ds:0xa611068,0x0
  514976:	00 00 00 
  514979:	6a 00                	push   0x0
  51497b:	52                   	push   edx
  51497c:	50                   	push   eax
  51497d:	8b ce                	mov    ecx,esi
  51497f:	e8 bc f9 ff ff       	call   0x514340
  514984:	83 c4 0c             	add    esp,0xc
  514987:	83 c6 08             	add    esi,0x8
  51498a:	8b 95 5c ff ff ff    	mov    edx,DWORD PTR [ebp-0xa4]
  514990:	43                   	inc    ebx
  514991:	8b c2                	mov    eax,edx

; Original CFAF0 text widths and markup deductions.
  4cfbfa:	ff d6                	call   esi
  4cfbfc:	83 c4 08             	add    esp,0x8
  4cfbff:	85 c0                	test   eax,eax
  4cfc01:	74 1b                	je     0x4cfc1e
  4cfc03:	8d 8d f8 fb ff ff    	lea    ecx,[ebp-0x408]
  4cfc09:	2b c1                	sub    eax,ecx
  4cfc0b:	3d 00 04 00 00       	cmp    eax,0x400
  4cfc10:	0f 83 e6 00 00 00    	jae    0x4cfcfc
  4cfc16:	c6 84 05 f8 fb ff ff 	mov    BYTE PTR [ebp+eax*1-0x408],0x0
  4cfc1d:	00 
  4cfc1e:	8d 8d f8 fb ff ff    	lea    ecx,[ebp-0x408]
  4cfc24:	8d 51 01             	lea    edx,[ecx+0x1]
  4cfc27:	8a 01                	mov    al,BYTE PTR [ecx]
  4cfc29:	41                   	inc    ecx
  4cfc2a:	84 c0                	test   al,al
  4cfc2c:	75 f9                	jne    0x4cfc27
  4cfc2e:	8b bd f0 fb ff ff    	mov    edi,DWORD PTR [ebp-0x410]
  4cfc34:	2b ca                	sub    ecx,edx
  4cfc36:	69 15 34 4a 35 06 e8 	imul   edx,DWORD PTR ds:0x6354a34,0xe8
  4cfc3d:	00 00 00 
  4cfc40:	8d 04 cd 0a 00 00 00 	lea    eax,[ecx*8+0xa]
  4cfc47:	8b cf                	mov    ecx,edi
  4cfc49:	8d 59 01             	lea    ebx,[ecx+0x1]
  4cfc4c:	89 82 f4 ef 34 06    	mov    DWORD PTR [edx+0x634eff4],eax
  4cfc52:	8a 01                	mov    al,BYTE PTR [ecx]
  4cfc54:	41                   	inc    ecx
  4cfc55:	84 c0                	test   al,al
  4cfc57:	75 f9                	jne    0x4cfc52
  4cfc59:	2b cb                	sub    ecx,ebx
  4cfc5b:	6a 3c                	push   0x3c
  4cfc5d:	8d 04 cd 0a 00 00 00 	lea    eax,[ecx*8+0xa]
  4cfc64:	89 82 e8 ef 34 06    	mov    DWORD PTR [edx+0x634efe8],eax
  4cfc6a:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  4cfc70:	50                   	push   eax
  4cfc71:	ff d6                	call   esi
  4cfc73:	83 c4 08             	add    esp,0x8
  4cfc76:	85 c0                	test   eax,eax
  4cfc78:	74 18                	je     0x4cfc92
  4cfc7a:	69 05 34 4a 35 06 e8 	imul   eax,DWORD PTR ds:0x6354a34,0xe8
  4cfc81:	00 00 00 
  4cfc84:	83 80 e8 ef 34 06 f0 	add    DWORD PTR [eax+0x634efe8],0xfffffff0
  4cfc8b:	83 80 f4 ef 34 06 f0 	add    DWORD PTR [eax+0x634eff4],0xfffffff0
  4cfc92:	6a 2e                	push   0x2e
  4cfc94:	57                   	push   edi
  4cfc95:	ff d6                	call   esi
  4cfc97:	8b 15 34 4a 35 06    	mov    edx,DWORD PTR ds:0x6354a34
  4cfc9d:	83 c4 08             	add    esp,0x8
  4cfca0:	69 ca e8 00 00 00    	imul   ecx,edx,0xe8
  4cfca6:	81 c1 10 ef 34 06    	add    ecx,0x634ef10
  4cfcac:	85 c0                	test   eax,eax
  4cfcae:	75 20                	jne    0x4cfcd0
  4cfcb0:	f3 0f 7e 05 f4 4d 5a 	movq   xmm0,QWORD PTR ds:0x5a4df4
  4cfcb7:	00 
  4cfcb8:	66 a1 fc 4d 5a 00    	mov    ax,ds:0x5a4dfc
  4cfcbe:	66 0f d6 01          	movq   QWORD PTR [ecx],xmm0
  4cfcc2:	66 89 41 08          	mov    WORD PTR [ecx+0x8],ax
  4cfcc6:	a0 fe 4d 5a 00       	mov    al,ds:0x5a4dfe
  4cfccb:	88 41 0a             	mov    BYTE PTR [ecx+0xa],al
  4cfcce:	eb 14                	jmp    0x4cfce4
