
/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

004f8740 <.text+0xf7740>:
  4f8740:	55                   	push   ebp
  4f8741:	8b ec                	mov    ebp,esp
  4f8743:	83 ec 34             	sub    esp,0x34
  4f8746:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  4f874b:	33 c5                	xor    eax,ebp
  4f874d:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  4f8750:	53                   	push   ebx
  4f8751:	56                   	push   esi
  4f8752:	33 f6                	xor    esi,esi
  4f8754:	89 4d d0             	mov    DWORD PTR [ebp-0x30],ecx
  4f8757:	57                   	push   edi
  4f8758:	32 db                	xor    bl,bl
  4f875a:	8b fa                	mov    edi,edx
  4f875c:	83 fe 08             	cmp    esi,0x8
  4f875f:	0f 83 46 01 00 00    	jae    0x4f88ab
  4f8765:	0f 28 05 30 db 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5ddb30
  4f876c:	0f 11 45 d4          	movups XMMWORD PTR [ebp-0x2c],xmm0
  4f8770:	c6 44 35 f4 00       	mov    BYTE PTR [ebp+esi*1-0xc],0x0
  4f8775:	0f 28 05 e0 d7 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5dd7e0
  4f877c:	0f 11 45 e4          	movups XMMWORD PTR [ebp-0x1c],xmm0
  4f8780:	0f bf 4c b5 d4       	movsx  ecx,WORD PTR [ebp+esi*4-0x2c]
  4f8785:	0f 28 05 40 db 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5ddb40
  4f878c:	03 0d 9c 1c 6d 0a    	add    ecx,DWORD PTR ds:0xa6d1c9c
  4f8792:	0f 11 45 d4          	movups XMMWORD PTR [ebp-0x2c],xmm0
  4f8796:	0f 28 05 f0 d7 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5dd7f0
  4f879d:	0f 11 45 e4          	movups XMMWORD PTR [ebp-0x1c],xmm0
  4f87a1:	0f bf 44 b5 d4       	movsx  eax,WORD PTR [ebp+esi*4-0x2c]
  4f87a6:	03 05 40 bd 72 0a    	add    eax,DWORD PTR ds:0xa72bd40
  4f87ac:	81 f9 ff 0b 00 00    	cmp    ecx,0xbff
  4f87b2:	77 16                	ja     0x4f87ca
  4f87b4:	3d ff 07 00 00       	cmp    eax,0x7ff
  4f87b9:	77 0f                	ja     0x4f87ca
  4f87bb:	69 c0 01 0c 00 00    	imul   eax,eax,0xc01
  4f87c1:	8a 84 08 48 94 cf 00 	mov    al,BYTE PTR [eax+ecx*1+0xcf9448]
  4f87c8:	eb 02                	jmp    0x4f87cc
  4f87ca:	b0 20                	mov    al,0x20
  4f87cc:	0f b6 c0             	movzx  eax,al
  4f87cf:	50                   	push   eax
  4f87d0:	57                   	push   edi
  4f87d1:	ff 15 48 c3 58 00    	call   DWORD PTR ds:0x58c348
  4f87d7:	83 c4 08             	add    esp,0x8
  4f87da:	85 c0                	test   eax,eax
  4f87dc:	74 07                	je     0x4f87e5
  4f87de:	c6 44 35 f4 01       	mov    BYTE PTR [ebp+esi*1-0xc],0x1
  4f87e3:	fe c3                	inc    bl
  4f87e5:	46                   	inc    esi
  4f87e6:	83 fe 08             	cmp    esi,0x8
  4f87e9:	0f 8c 70 ff ff ff    	jl     0x4f875f
  4f87ef:	80 fb 01             	cmp    bl,0x1
  4f87f2:	75 0f                	jne    0x4f8803
  4f87f4:	33 c0                	xor    eax,eax
  4f87f6:	80 7c 05 f4 00       	cmp    BYTE PTR [ebp+eax*1-0xc],0x0
  4f87fb:	75 21                	jne    0x4f881e
  4f87fd:	40                   	inc    eax
  4f87fe:	83 f8 08             	cmp    eax,0x8
  4f8801:	7c f3                	jl     0x4f87f6
  4f8803:	8b 55 d0             	mov    edx,DWORD PTR [ebp-0x30]
  4f8806:	b1 06                	mov    cl,0x6
  4f8808:	e8 13 f0 ff ff       	call   0x4f7820
  4f880d:	5f                   	pop    edi
  4f880e:	5e                   	pop    esi
  4f880f:	5b                   	pop    ebx
  4f8810:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  4f8813:	33 cd                	xor    ecx,ebp
  4f8815:	e8 94 18 09 00       	call   0x58a0ae
  4f881a:	8b e5                	mov    esp,ebp
  4f881c:	5d                   	pop    ebp
  4f881d:	c3                   	ret
  4f881e:	0f 28 05 30 db 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5ddb30
  4f8825:	0f 11 45 d4          	movups XMMWORD PTR [ebp-0x2c],xmm0
  4f8829:	0f 28 05 e0 d7 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5dd7e0
  4f8830:	0f 11 45 e4          	movups XMMWORD PTR [ebp-0x1c],xmm0
  4f8834:	0f bf 4c 85 d4       	movsx  ecx,WORD PTR [ebp+eax*4-0x2c]
  4f8839:	0f 28 05 40 db 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5ddb40
  4f8840:	03 0d 9c 1c 6d 0a    	add    ecx,DWORD PTR ds:0xa6d1c9c
  4f8846:	0f 11 45 d4          	movups XMMWORD PTR [ebp-0x2c],xmm0
  4f884a:	89 0d 3c bd 72 0a    	mov    DWORD PTR ds:0xa72bd3c,ecx
  4f8850:	0f 28 05 f0 d7 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5dd7f0
  4f8857:	0f 11 45 e4          	movups XMMWORD PTR [ebp-0x1c],xmm0
  4f885b:	0f bf 44 85 d4       	movsx  eax,WORD PTR [ebp+eax*4-0x2c]
  4f8860:	03 05 40 bd 72 0a    	add    eax,DWORD PTR ds:0xa72bd40
  4f8866:	a3 34 1c 6d 0a       	mov    ds:0xa6d1c34,eax
  4f886b:	81 f9 ff 0b 00 00    	cmp    ecx,0xbff
  4f8871:	77 25                	ja     0x4f8898
  4f8873:	3d ff 07 00 00       	cmp    eax,0x7ff
  4f8878:	77 1e                	ja     0x4f8898
  4f887a:	69 c0 01 0c 00 00    	imul   eax,eax,0xc01
  4f8880:	8a 84 08 48 94 cf 00 	mov    al,BYTE PTR [eax+ecx*1+0xcf9448]
  4f8887:	5f                   	pop    edi
  4f8888:	5e                   	pop    esi
  4f8889:	5b                   	pop    ebx
  4f888a:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  4f888d:	33 cd                	xor    ecx,ebp
  4f888f:	e8 1a 18 09 00       	call   0x58a0ae
  4f8894:	8b e5                	mov    esp,ebp
  4f8896:	5d                   	pop    ebp
  4f8897:	c3                   	ret
  4f8898:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  4f889b:	b0 20                	mov    al,0x20
  4f889d:	5f                   	pop    edi
  4f889e:	5e                   	pop    esi
  4f889f:	33 cd                	xor    ecx,ebp
  4f88a1:	5b                   	pop    ebx
  4f88a2:	e8 07 18 09 00       	call   0x58a0ae
  4f88a7:	8b e5                	mov    esp,ebp
  4f88a9:	5d                   	pop    ebp
  4f88aa:	c3                   	ret
  4f88ab:	e8 32 19 09 00       	call   0x58a1e2
  4f88b0:	cc                   	int3
  4f88b1:	cc                   	int3
  4f88b2:	cc                   	int3
  4f88b3:	cc                   	int3
  4f88b4:	cc                   	int3
  4f88b5:	cc                   	int3
  4f88b6:	cc                   	int3
  4f88b7:	cc                   	int3
  4f88b8:	cc                   	int3
  4f88b9:	cc                   	int3
  4f88ba:	cc                   	int3
  4f88bb:	cc                   	int3
  4f88bc:	cc                   	int3
  4f88bd:	cc                   	int3
  4f88be:	cc                   	int3
  4f88bf:	cc                   	int3
  4f88c0:	55                   	push   ebp
  4f88c1:	8b ec                	mov    ebp,esp
  4f88c3:	83 ec 50             	sub    esp,0x50
  4f88c6:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  4f88cb:	33 c5                	xor    eax,ebp
  4f88cd:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  4f88d0:	f6 45 10 04          	test   BYTE PTR [ebp+0x10],0x4
  4f88d4:	8b 45 08             	mov    eax,DWORD PTR [ebp+0x8]
  4f88d7:	53                   	push   ebx
  4f88d8:	8b 1d 40 bd 72 0a    	mov    ebx,DWORD PTR ds:0xa72bd40
  4f88de:	56                   	push   esi
  4f88df:	89 45 d8             	mov    DWORD PTR [ebp-0x28],eax
  4f88e2:	8b 45 0c             	mov    eax,DWORD PTR [ebp+0xc]
  4f88e5:	57                   	push   edi
  4f88e6:	89 55 d0             	mov    DWORD PTR [ebp-0x30],edx
  4f88e9:	89 4d b4             	mov    DWORD PTR [ebp-0x4c],ecx
  4f88ec:	89 45 d4             	mov    DWORD PTR [ebp-0x2c],eax
  4f88ef:	74 59                	je     0x4f894a
  4f88f1:	8b 3d 9c 1c 6d 0a    	mov    edi,DWORD PTR ds:0xa6d1c9c
  4f88f7:	8b f3                	mov    esi,ebx
  4f88f9:	8b 4d d0             	mov    ecx,DWORD PTR [ebp-0x30]
  4f88fc:	8b d7                	mov    edx,edi
  4f88fe:	56                   	push   esi
  4f88ff:	e8 2c 0b f2 ff       	call   0x419430
  4f8904:	83 c4 04             	add    esp,0x4
  4f8907:	8b d0                	mov    edx,eax
  4f8909:	83 7d d0 34          	cmp    DWORD PTR [ebp-0x30],0x34
  4f890d:	75 36                	jne    0x4f8945
  4f890f:	83 fa ff             	cmp    edx,0xffffffff
  4f8912:	74 36                	je     0x4f894a
  4f8914:	f6 45 10 08          	test   BYTE PTR [ebp+0x10],0x8
  4f8918:	74 2b                	je     0x4f8945
  4f891a:	8d 04 d2             	lea    eax,[edx+edx*8]
  4f891d:	8b 04 85 b4 28 6d 0a 	mov    eax,DWORD PTR [eax*4+0xa6d28b4]
  4f8924:	3d e8 03 00 00       	cmp    eax,0x3e8
  4f8929:	7c 05                	jl     0x4f8930
  4f892b:	05 18 fc ff ff       	add    eax,0xfffffc18
  4f8930:	69 c8 68 05 00 00    	imul   ecx,eax,0x568
  4f8936:	81 c1 00 14 15 06    	add    ecx,0x6151400
  4f893c:	e8 bf 4c f1 ff       	call   0x40d600
  4f8941:	85 c0                	test   eax,eax
  4f8943:	75 05                	jne    0x4f894a
  4f8945:	83 fa ff             	cmp    edx,0xffffffff
  4f8948:	75 53                	jne    0x4f899d
  4f894a:	0f 28 05 30 db 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5ddb30
  4f8951:	a1 10 41 78 0a       	mov    eax,ds:0xa784110
  4f8956:	8b 4d d0             	mov    ecx,DWORD PTR [ebp-0x30]
  4f8959:	0f 11 45 dc          	movups XMMWORD PTR [ebp-0x24],xmm0
  4f895d:	0f 28 05 e0 d7 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5dd7e0
  4f8964:	0f 11 45 ec          	movups XMMWORD PTR [ebp-0x14],xmm0
  4f8968:	0f bf 7c 85 dc       	movsx  edi,WORD PTR [ebp+eax*4-0x24]
  4f896d:	0f 28 05 40 db 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5ddb40
  4f8974:	03 3d 9c 1c 6d 0a    	add    edi,DWORD PTR ds:0xa6d1c9c
  4f897a:	0f 11 45 dc          	movups XMMWORD PTR [ebp-0x24],xmm0
  4f897e:	8b d7                	mov    edx,edi
  4f8980:	0f 28 05 f0 d7 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5dd7f0
  4f8987:	0f 11 45 ec          	movups XMMWORD PTR [ebp-0x14],xmm0
  4f898b:	0f bf 74 85 dc       	movsx  esi,WORD PTR [ebp+eax*4-0x24]
  4f8990:	03 f3                	add    esi,ebx
  4f8992:	56                   	push   esi
  4f8993:	e8 98 0a f2 ff       	call   0x419430
  4f8998:	83 c4 04             	add    esp,0x4
  4f899b:	8b d0                	mov    edx,eax
  4f899d:	83 7d d0 34          	cmp    DWORD PTR [ebp-0x30],0x34
  4f89a1:	75 36                	jne    0x4f89d9
  4f89a3:	83 fa ff             	cmp    edx,0xffffffff
  4f89a6:	74 78                	je     0x4f8a20
  4f89a8:	f6 45 10 08          	test   BYTE PTR [ebp+0x10],0x8
  4f89ac:	74 2b                	je     0x4f89d9
  4f89ae:	8d 04 d2             	lea    eax,[edx+edx*8]
  4f89b1:	8b 04 85 b4 28 6d 0a 	mov    eax,DWORD PTR [eax*4+0xa6d28b4]
  4f89b8:	3d e8 03 00 00       	cmp    eax,0x3e8
  4f89bd:	7c 05                	jl     0x4f89c4
  4f89bf:	05 18 fc ff ff       	add    eax,0xfffffc18
  4f89c4:	69 c8 68 05 00 00    	imul   ecx,eax,0x568
  4f89ca:	81 c1 00 14 15 06    	add    ecx,0x6151400
  4f89d0:	e8 2b 4c f1 ff       	call   0x40d600
  4f89d5:	85 c0                	test   eax,eax
  4f89d7:	75 47                	jne    0x4f8a20
  4f89d9:	83 fa ff             	cmp    edx,0xffffffff
  4f89dc:	74 42                	je     0x4f8a20
  4f89de:	8b 45 d8             	mov    eax,DWORD PTR [ebp-0x28]
  4f89e1:	8b 4d d4             	mov    ecx,DWORD PTR [ebp-0x2c]
  4f89e4:	89 38                	mov    DWORD PTR [eax],edi
  4f89e6:	89 31                	mov    DWORD PTR [ecx],esi
  4f89e8:	8b 08                	mov    ecx,DWORD PTR [eax]
  4f89ea:	81 f9 ff 0b 00 00    	cmp    ecx,0xbff
  4f89f0:	0f 87 b5 01 00 00    	ja     0x4f8bab
  4f89f6:	81 fe ff 07 00 00    	cmp    esi,0x7ff
  4f89fc:	0f 87 a9 01 00 00    	ja     0x4f8bab
  4f8a02:	69 c6 01 0c 00 00    	imul   eax,esi,0xc01
  4f8a08:	8a 84 08 48 94 cf 00 	mov    al,BYTE PTR [eax+ecx*1+0xcf9448]
  4f8a0f:	5f                   	pop    edi
  4f8a10:	5e                   	pop    esi
  4f8a11:	5b                   	pop    ebx
  4f8a12:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  4f8a15:	33 cd                	xor    ecx,ebp
  4f8a17:	e8 92 16 09 00       	call   0x58a0ae
  4f8a1c:	8b e5                	mov    esp,ebp
  4f8a1e:	5d                   	pop    ebp
  4f8a1f:	c3                   	ret
  4f8a20:	f6 45 10 01          	test   BYTE PTR [ebp+0x10],0x1
  4f8a24:	8b 75 d8             	mov    esi,DWORD PTR [ebp-0x28]
  4f8a27:	0f 84 1f 01 00 00    	je     0x4f8b4c
  4f8a2d:	8b 55 d4             	mov    edx,DWORD PTR [ebp-0x2c]
  4f8a30:	8d 4b 02             	lea    ecx,[ebx+0x2]
  4f8a33:	33 c0                	xor    eax,eax
  4f8a35:	c7 06 00 00 00 00    	mov    DWORD PTR [esi],0x0
  4f8a3b:	8d 7b ff             	lea    edi,[ebx-0x1]
  4f8a3e:	89 45 cc             	mov    DWORD PTR [ebp-0x34],eax
  4f8a41:	89 4d bc             	mov    DWORD PTR [ebp-0x44],ecx
  4f8a44:	c7 02 00 00 00 00    	mov    DWORD PTR [edx],0x0
  4f8a4a:	3b f9                	cmp    edi,ecx
  4f8a4c:	0f 8d fa 00 00 00    	jge    0x4f8b4c
  4f8a52:	8b 0d 9c 1c 6d 0a    	mov    ecx,DWORD PTR ds:0xa6d1c9c
  4f8a58:	8d 71 ff             	lea    esi,[ecx-0x1]
  4f8a5b:	83 c1 02             	add    ecx,0x2
  4f8a5e:	89 4d c0             	mov    DWORD PTR [ebp-0x40],ecx
  4f8a61:	69 cf 01 0c 00 00    	imul   ecx,edi,0xc01
  4f8a67:	89 75 b8             	mov    DWORD PTR [ebp-0x48],esi
  4f8a6a:	81 c1 58 54 78 02    	add    ecx,0x2785458
  4f8a70:	2b df                	sub    ebx,edi
  4f8a72:	89 4d c4             	mov    DWORD PTR [ebp-0x3c],ecx
  4f8a75:	89 5d c8             	mov    DWORD PTR [ebp-0x38],ebx
  4f8a78:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [eax+eax*1+0x0]
  4f8a7f:	00 
  4f8a80:	3b 75 c0             	cmp    esi,DWORD PTR [ebp-0x40]
  4f8a83:	0f 8d 98 00 00 00    	jge    0x4f8b21
  4f8a89:	8b 1d 9c 1c 6d 0a    	mov    ebx,DWORD PTR ds:0xa6d1c9c
  4f8a8f:	2b de                	sub    ebx,esi
  4f8a91:	8b 4d d0             	mov    ecx,DWORD PTR [ebp-0x30]
  4f8a94:	8b d6                	mov    edx,esi
  4f8a96:	57                   	push   edi
  4f8a97:	e8 94 09 f2 ff       	call   0x419430
  4f8a9c:	83 c4 04             	add    esp,0x4
  4f8a9f:	83 f8 ff             	cmp    eax,0xffffffff
  4f8aa2:	74 66                	je     0x4f8b0a
  4f8aa4:	33 c9                	xor    ecx,ecx
  4f8aa6:	83 ff 01             	cmp    edi,0x1
  4f8aa9:	0f 9c c1             	setl   cl
  4f8aac:	33 c0                	xor    eax,eax
  4f8aae:	83 fe 01             	cmp    esi,0x1
  4f8ab1:	0f 9c c0             	setl   al
  4f8ab4:	0b c8                	or     ecx,eax
  4f8ab6:	75 39                	jne    0x4f8af1
  4f8ab8:	8b c3                	mov    eax,ebx
  4f8aba:	99                   	cdq
  4f8abb:	33 c2                	xor    eax,edx
  4f8abd:	2b c2                	sub    eax,edx
  4f8abf:	3b 05 d4 b5 5b 06    	cmp    eax,DWORD PTR ds:0x65bb5d4
  4f8ac5:	7f 2a                	jg     0x4f8af1
  4f8ac7:	8b 45 c8             	mov    eax,DWORD PTR [ebp-0x38]
  4f8aca:	99                   	cdq
  4f8acb:	33 c2                	xor    eax,edx
  4f8acd:	2b c2                	sub    eax,edx
  4f8acf:	3b 05 d8 b5 5b 06    	cmp    eax,DWORD PTR ds:0x65bb5d8
  4f8ad5:	7f 1a                	jg     0x4f8af1
  4f8ad7:	81 fe ff 0b 00 00    	cmp    esi,0xbff
  4f8add:	77 12                	ja     0x4f8af1
  4f8adf:	81 ff ff 07 00 00    	cmp    edi,0x7ff
  4f8ae5:	77 0a                	ja     0x4f8af1
  4f8ae7:	8b 45 c4             	mov    eax,DWORD PTR [ebp-0x3c]
  4f8aea:	8a 04 30             	mov    al,BYTE PTR [eax+esi*1]
  4f8aed:	3c 3a                	cmp    al,0x3a
  4f8aef:	75 06                	jne    0x4f8af7
  4f8af1:	f6 45 10 02          	test   BYTE PTR [ebp+0x10],0x2
  4f8af5:	75 13                	jne    0x4f8b0a
  4f8af7:	8b 4d d8             	mov    ecx,DWORD PTR [ebp-0x28]
  4f8afa:	8b 45 cc             	mov    eax,DWORD PTR [ebp-0x34]
  4f8afd:	8b 55 d4             	mov    edx,DWORD PTR [ebp-0x2c]
  4f8b00:	40                   	inc    eax
  4f8b01:	89 45 cc             	mov    DWORD PTR [ebp-0x34],eax
  4f8b04:	89 31                	mov    DWORD PTR [ecx],esi
  4f8b06:	89 3a                	mov    DWORD PTR [edx],edi
  4f8b08:	eb 06                	jmp    0x4f8b10
  4f8b0a:	8b 55 d4             	mov    edx,DWORD PTR [ebp-0x2c]
  4f8b0d:	8b 45 cc             	mov    eax,DWORD PTR [ebp-0x34]
  4f8b10:	46                   	inc    esi
  4f8b11:	4b                   	dec    ebx
  4f8b12:	3b 75 c0             	cmp    esi,DWORD PTR [ebp-0x40]
  4f8b15:	0f 8c 76 ff ff ff    	jl     0x4f8a91
  4f8b1b:	8b 4d c4             	mov    ecx,DWORD PTR [ebp-0x3c]
  4f8b1e:	8b 5d c8             	mov    ebx,DWORD PTR [ebp-0x38]
  4f8b21:	8b 75 b8             	mov    esi,DWORD PTR [ebp-0x48]
  4f8b24:	47                   	inc    edi
  4f8b25:	4b                   	dec    ebx
  4f8b26:	81 c1 01 0c 00 00    	add    ecx,0xc01
  4f8b2c:	89 5d c8             	mov    DWORD PTR [ebp-0x38],ebx
  4f8b2f:	89 4d c4             	mov    DWORD PTR [ebp-0x3c],ecx
  4f8b32:	3b 7d bc             	cmp    edi,DWORD PTR [ebp-0x44]
  4f8b35:	0f 8c 45 ff ff ff    	jl     0x4f8a80
  4f8b3b:	83 f8 01             	cmp    eax,0x1
  4f8b3e:	75 09                	jne    0x4f8b49
  4f8b40:	8b 4d d8             	mov    ecx,DWORD PTR [ebp-0x28]
  4f8b43:	8b 02                	mov    eax,DWORD PTR [edx]
  4f8b45:	8b 09                	mov    ecx,DWORD PTR [ecx]
  4f8b47:	eb 35                	jmp    0x4f8b7e
  4f8b49:	8b 75 d8             	mov    esi,DWORD PTR [ebp-0x28]
  4f8b4c:	8b 55 b4             	mov    edx,DWORD PTR [ebp-0x4c]
  4f8b4f:	b1 02                	mov    cl,0x2
  4f8b51:	e8 ca ec ff ff       	call   0x4f7820
  4f8b56:	84 c0                	test   al,al
  4f8b58:	75 11                	jne    0x4f8b6b
  4f8b5a:	5f                   	pop    edi
  4f8b5b:	5e                   	pop    esi
  4f8b5c:	5b                   	pop    ebx
  4f8b5d:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  4f8b60:	33 cd                	xor    ecx,ebp
  4f8b62:	e8 47 15 09 00       	call   0x58a0ae
  4f8b67:	8b e5                	mov    esp,ebp
  4f8b69:	5d                   	pop    ebp
  4f8b6a:	c3                   	ret
  4f8b6b:	8b 4d d4             	mov    ecx,DWORD PTR [ebp-0x2c]
  4f8b6e:	a1 3c bd 72 0a       	mov    eax,ds:0xa72bd3c
  4f8b73:	89 06                	mov    DWORD PTR [esi],eax
  4f8b75:	a1 34 1c 6d 0a       	mov    eax,ds:0xa6d1c34
  4f8b7a:	89 01                	mov    DWORD PTR [ecx],eax
  4f8b7c:	8b 0e                	mov    ecx,DWORD PTR [esi]
  4f8b7e:	81 f9 ff 0b 00 00    	cmp    ecx,0xbff
  4f8b84:	77 25                	ja     0x4f8bab
  4f8b86:	3d ff 07 00 00       	cmp    eax,0x7ff
  4f8b8b:	77 1e                	ja     0x4f8bab
  4f8b8d:	69 c0 01 0c 00 00    	imul   eax,eax,0xc01
  4f8b93:	8a 84 08 48 94 cf 00 	mov    al,BYTE PTR [eax+ecx*1+0xcf9448]
  4f8b9a:	5f                   	pop    edi
  4f8b9b:	5e                   	pop    esi
  4f8b9c:	5b                   	pop    ebx
  4f8b9d:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  4f8ba0:	33 cd                	xor    ecx,ebp
  4f8ba2:	e8 07 15 09 00       	call   0x58a0ae
  4f8ba7:	8b e5                	mov    esp,ebp
  4f8ba9:	5d                   	pop    ebp
  4f8baa:	c3                   	ret
  4f8bab:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  4f8bae:	b0 20                	mov    al,0x20
  4f8bb0:	5f                   	pop    edi
  4f8bb1:	5e                   	pop    esi
  4f8bb2:	33 cd                	xor    ecx,ebp
  4f8bb4:	5b                   	pop    ebx
  4f8bb5:	e8 f4 14 09 00       	call   0x58a0ae
  4f8bba:	8b e5                	mov    esp,ebp
  4f8bbc:	5d                   	pop    ebp
  4f8bbd:	c3                   	ret
  4f8bbe:	cc                   	int3
  4f8bbf:	cc                   	int3
  4f8bc0:	8b d1                	mov    edx,ecx
  4f8bc2:	b1 02                	mov    cl,0x2
  4f8bc4:	56                   	push   esi
  4f8bc5:	e8 56 ec ff ff       	call   0x4f7820
  4f8bca:	8a d0                	mov    dl,al
  4f8bcc:	84 d2                	test   dl,dl
  4f8bce:	74 3b                	je     0x4f8c0b
  4f8bd0:	80 fa 51             	cmp    dl,0x51
  4f8bd3:	74 2c                	je     0x4f8c01
  4f8bd5:	33 c9                	xor    ecx,ecx
  4f8bd7:	0f b6 f2             	movzx  esi,dl
  4f8bda:	81 fe ff 00 00 00    	cmp    esi,0xff
  4f8be0:	0f 9f c1             	setg   cl
  4f8be3:	33 c0                	xor    eax,eax
  4f8be5:	85 f6                	test   esi,esi
  4f8be7:	0f 98 c0             	sets   al
  4f8bea:	0b c8                	or     ecx,eax
  4f8bec:	75 0f                	jne    0x4f8bfd
  4f8bee:	69 c6 58 02 00 00    	imul   eax,esi,0x258
  4f8bf4:	f6 80 9c c7 5e 00 04 	test   BYTE PTR [eax+0x5ec79c],0x4
  4f8bfb:	75 04                	jne    0x4f8c01
  4f8bfd:	8a c2                	mov    al,dl
  4f8bff:	5e                   	pop    esi
  4f8c00:	c3                   	ret
  4f8c01:	b9 d8 a0 5a 00       	mov    ecx,0x5aa0d8
  4f8c06:	e8 05 d9 ff ff       	call   0x4f6510
  4f8c0b:	32 c0                	xor    al,al
  4f8c0d:	5e                   	pop    esi
  4f8c0e:	c3                   	ret
  4f8c0f:	cc                   	int3
