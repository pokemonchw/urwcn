; Windows 3.89.1, image base 00400000. Offline excerpt only.
; Source: build/analysis/windows-3891-native-full.asm

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
  4e8dd7:	83 c4 1c             	add    esp,0x1c
  4e8dda:	85 db                	test   ebx,ebx
  4e8ddc:	78 18                	js     0x4e8df6

  4e8df6:	81 fb 48 f4 ff ff    	cmp    ebx,0xfffff448
  4e8dfc:	75 11                	jne    0x4e8e0f
  4e8dfe:	b9 40 8a 5a 00       	mov    ecx,0x5a8a40
  4e8e03:	e8 38 9f 07 00       	call   0x562d40
  4e8e08:	8b c8                	mov    ecx,eax
  4e8e0a:	e8 01 d7 00 00       	call   0x4f6510
  4e8e0f:	33 c0                	xor    eax,eax

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
  455770:	83 c4 0c             	add    esp,0xc
