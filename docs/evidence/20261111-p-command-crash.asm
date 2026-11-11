# Original Windows x86 PE 3.89.1; preferred base 00400000.
# SHA-256 c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d
# Extracted offline from build/analysis/windows-3891-native-full.asm. No game execution.

# VA 004554D1..00455513 (exclusive end)
  4554d1:	8b 7d 1c             	mov    edi,DWORD PTR [ebp+0x1c]
  4554d4:	83 c4 0c             	add    esp,0xc
  4554d7:	8b 55 18             	mov    edx,DWORD PTR [ebp+0x18]
  4554da:	8b cf                	mov    ecx,edi
  4554dc:	c7 05 1c 71 6f 00 00 	mov    DWORD PTR ds:0x6f711c,0x0
  4554e3:	00 00 00 
  4554e6:	e8 b5 de ff ff       	call   0x4533a0
  4554eb:	8b d0                	mov    edx,eax
  4554ed:	89 54 24 4c          	mov    DWORD PTR [esp+0x4c],edx
  4554f1:	85 d2                	test   edx,edx
  4554f3:	75 1e                	jne    0x455513
  4554f5:	85 ff                	test   edi,edi
  4554f7:	75 1a                	jne    0x455513
  4554f9:	b8 48 f4 ff ff       	mov    eax,0xfffff448
  4554fe:	5f                   	pop    edi
  4554ff:	5e                   	pop    esi
  455500:	5b                   	pop    ebx
  455501:	8b 8c 24 c0 14 00 00 	mov    ecx,DWORD PTR [esp+0x14c0]
  455508:	33 cc                	xor    ecx,esp
  45550a:	e8 9f 4b 13 00       	call   0x58a0ae
  45550f:	8b e5                	mov    esp,ebp
  455511:	5d                   	pop    ebp
  455512:	c3                   	ret

# VA 00458EB0..00458F70 (exclusive end)
  458eb0:	55                   	push   ebp
  458eb1:	8b ec                	mov    ebp,esp
  458eb3:	81 ec a8 01 00 00    	sub    esp,0x1a8
  458eb9:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  458ebe:	33 c5                	xor    eax,ebp
  458ec0:	89 45 f8             	mov    DWORD PTR [ebp-0x8],eax
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
  458f23:	83 c4 1c             	add    esp,0x1c
  458f26:	81 fe 48 f4 ff ff    	cmp    esi,0xfffff448
  458f2c:	75 36                	jne    0x458f64
  458f2e:	b9 fc 5e 59 00       	mov    ecx,0x595efc
  458f33:	e8 c8 8b 10 00       	call   0x561b00
  458f38:	8b c8                	mov    ecx,eax
  458f3a:	e8 d1 d5 09 00       	call   0x4f6510
  458f3f:	68 00 04 00 00       	push   0x400
  458f44:	6a 00                	push   0x0
  458f46:	68 c0 6a 5e 00       	push   0x5e6ac0
  458f4b:	e8 10 1f 13 00       	call   0x58ae60
  458f50:	83 c4 0c             	add    esp,0xc
  458f53:	5f                   	pop    edi
  458f54:	5e                   	pop    esi
  458f55:	5b                   	pop    ebx
  458f56:	8b 4d f8             	mov    ecx,DWORD PTR [ebp-0x8]
  458f59:	33 cd                	xor    ecx,ebp
  458f5b:	e8 4e 11 13 00       	call   0x58a0ae
  458f60:	8b e5                	mov    esp,ebp
  458f62:	5d                   	pop    ebp
  458f63:	c3                   	ret
  458f64:	ba 5c 61 59 00       	mov    edx,0x59615c
  458f69:	b1 06                	mov    cl,0x6
  458f6b:	e8 b0 e8 09 00       	call   0x4f7820

# VA 005642FB..0056431A (exclusive end)
  5642fb:	6a 00                	push   0x0
  5642fd:	33 d2                	xor    edx,edx
  5642ff:	33 c9                	xor    ecx,ecx
  564301:	e8 aa 4b ef ff       	call   0x458eb0
  564306:	83 c4 04             	add    esp,0x4
  564309:	5f                   	pop    edi
  56430a:	5e                   	pop    esi
  56430b:	5b                   	pop    ebx
  56430c:	8b 4d f8             	mov    ecx,DWORD PTR [ebp-0x8]
  56430f:	33 cd                	xor    ecx,ebp
  564311:	e8 98 5d 02 00       	call   0x58a0ae
  564316:	8b e5                	mov    esp,ebp
  564318:	5d                   	pop    ebp
  564319:	c3                   	ret

# VA 0058A0AE..0058A130 (exclusive end)
  58a0ae:	3b 0d 0c 20 5e 00    	cmp    ecx,DWORD PTR ds:0x5e200c
  58a0b4:	f2 75 02             	bnd jne 0x58a0b9
  58a0b7:	f2 c3                	bnd ret
  58a0b9:	f2 e9 28 00 00 00    	bnd jmp 0x58a0e7
  58a0bf:	55                   	push   ebp
  58a0c0:	8b ec                	mov    ebp,esp
  58a0c2:	6a 00                	push   0x0
  58a0c4:	ff 15 3c c0 58 00    	call   DWORD PTR ds:0x58c03c
  58a0ca:	ff 75 08             	push   DWORD PTR [ebp+0x8]
  58a0cd:	ff 15 40 c0 58 00    	call   DWORD PTR ds:0x58c040
  58a0d3:	68 09 04 00 c0       	push   0xc0000409
  58a0d8:	ff 15 38 c0 58 00    	call   DWORD PTR ds:0x58c038
  58a0de:	50                   	push   eax
  58a0df:	ff 15 34 c0 58 00    	call   DWORD PTR ds:0x58c034
  58a0e5:	5d                   	pop    ebp
  58a0e6:	c3                   	ret
  58a0e7:	55                   	push   ebp
  58a0e8:	8b ec                	mov    ebp,esp
  58a0ea:	81 ec 24 03 00 00    	sub    esp,0x324
  58a0f0:	6a 17                	push   0x17
  58a0f2:	e8 83 0f 00 00       	call   0x58b07a
  58a0f7:	85 c0                	test   eax,eax
  58a0f9:	74 05                	je     0x58a100
  58a0fb:	6a 02                	push   0x2
  58a0fd:	59                   	pop    ecx
  58a0fe:	cd 29                	int    0x29
  58a100:	a3 28 c1 5e 00       	mov    ds:0x5ec128,eax
  58a105:	89 0d 24 c1 5e 00    	mov    DWORD PTR ds:0x5ec124,ecx
  58a10b:	89 15 20 c1 5e 00    	mov    DWORD PTR ds:0x5ec120,edx
  58a111:	89 1d 1c c1 5e 00    	mov    DWORD PTR ds:0x5ec11c,ebx
  58a117:	89 35 18 c1 5e 00    	mov    DWORD PTR ds:0x5ec118,esi
  58a11d:	89 3d 14 c1 5e 00    	mov    DWORD PTR ds:0x5ec114,edi
  58a123:	66 8c 15 40 c1 5e 00 	data16 mov WORD PTR ds:0x5ec140,ss
  58a12a:	66 8c 0d 34 c1 5e 00 	data16 mov WORD PTR ds:0x5ec134,cs

# VA 0058A64C..0058A65E (exclusive end)
  58a64c:	e8 b4 05 00 00       	call   0x58ac05
  58a651:	e8 2a 07 00 00       	call   0x58ad80
  58a656:	50                   	push   eax
  58a657:	e8 94 08 00 00       	call   0x58aef0
  58a65c:	59                   	pop    ecx
  58a65d:	c3                   	ret

# VA 0058AB67..0058AB78 (exclusive end)
  58ab67:	ff 15 3c c0 58 00    	call   DWORD PTR ds:0x58c03c
  58ab6d:	8d 45 f8             	lea    eax,[ebp-0x8]
  58ab70:	50                   	push   eax
  58ab71:	ff 15 40 c0 58 00    	call   DWORD PTR ds:0x58c040
  58ab77:	85 c0                	test   eax,eax

# VA 0058AC05..0058AC52 (exclusive end)
  58ac05:	68 11 ac 58 00       	push   0x58ac11
  58ac0a:	ff 15 3c c0 58 00    	call   DWORD PTR ds:0x58c03c
  58ac10:	c3                   	ret
  58ac11:	55                   	push   ebp
  58ac12:	8b ec                	mov    ebp,esp
  58ac14:	8b 45 08             	mov    eax,DWORD PTR [ebp+0x8]
  58ac17:	8b 00                	mov    eax,DWORD PTR [eax]
  58ac19:	81 38 63 73 6d e0    	cmp    DWORD PTR [eax],0xe06d7363
  58ac1f:	75 25                	jne    0x58ac46
  58ac21:	83 78 10 03          	cmp    DWORD PTR [eax+0x10],0x3
  58ac25:	75 1f                	jne    0x58ac46
  58ac27:	8b 40 14             	mov    eax,DWORD PTR [eax+0x14]
  58ac2a:	3d 20 05 93 19       	cmp    eax,0x19930520
  58ac2f:	74 1b                	je     0x58ac4c
  58ac31:	3d 21 05 93 19       	cmp    eax,0x19930521
  58ac36:	74 14                	je     0x58ac4c
  58ac38:	3d 22 05 93 19       	cmp    eax,0x19930522
  58ac3d:	74 0d                	je     0x58ac4c
  58ac3f:	3d 00 40 99 01       	cmp    eax,0x1994000
  58ac44:	74 06                	je     0x58ac4c
  58ac46:	33 c0                	xor    eax,eax
  58ac48:	5d                   	pop    ebp
  58ac49:	c2 04 00             	ret    0x4
  58ac4c:	e8 ab 02 00 00       	call   0x58aefc
  58ac51:	cc                   	int3
