
/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

0050f950 <.text+0x10e950>:
  50f950:	55                   	push   ebp
  50f951:	8b ec                	mov    ebp,esp
  50f953:	83 ec 40             	sub    esp,0x40
  50f956:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  50f95b:	33 c5                	xor    eax,ebp
  50f95d:	89 45 f8             	mov    DWORD PTR [ebp-0x8],eax
  50f960:	a1 a8 b7 84 0a       	mov    eax,ds:0xa84b7a8
  50f965:	53                   	push   ebx
  50f966:	40                   	inc    eax
  50f967:	89 55 c8             	mov    DWORD PTR [ebp-0x38],edx
  50f96a:	89 4d cc             	mov    DWORD PTR [ebp-0x34],ecx
  50f96d:	56                   	push   esi
  50f96e:	57                   	push   edi
  50f96f:	25 ff 03 00 80       	and    eax,0x800003ff
  50f974:	79 07                	jns    0x50f97d
  50f976:	48                   	dec    eax
  50f977:	0d 00 fc ff ff       	or     eax,0xfffffc00
  50f97c:	40                   	inc    eax
  50f97d:	a3 a8 b7 84 0a       	mov    ds:0xa84b7a8,eax
  50f982:	c1 e0 0a             	shl    eax,0xa
  50f985:	68 00 04 00 00       	push   0x400
  50f98a:	6a 00                	push   0x0
  50f98c:	8d b0 b0 1e 94 0a    	lea    esi,[eax+0xa941eb0]
  50f992:	56                   	push   esi
  50f993:	89 75 c0             	mov    DWORD PTR [ebp-0x40],esi
  50f996:	e8 c5 b4 07 00       	call   0x58ae60
  50f99b:	66 0f 6e 05 bc 6a 5e 	movd   xmm0,DWORD PTR ds:0x5e6abc
  50f9a2:	00 
  50f9a3:	83 c4 0c             	add    esp,0xc
  50f9a6:	a1 34 56 35 06       	mov    eax,ds:0x6355634
  50f9ab:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  50f9ae:	89 45 c4             	mov    DWORD PTR [ebp-0x3c],eax
  50f9b1:	6a 00                	push   0x0
  50f9b3:	6a 00                	push   0x0
  50f9b5:	6a 00                	push   0x0
  50f9b7:	6a 00                	push   0x0
  50f9b9:	f3 0f 2c c0          	cvttss2si eax,xmm0
  50f9bd:	6a 20                	push   0x20
  50f9bf:	83 c0 02             	add    eax,0x2
  50f9c2:	50                   	push   eax
  50f9c3:	68 04 02 00 00       	push   0x204
  50f9c8:	6a 00                	push   0x0
  50f9ca:	ff 15 f0 c1 58 00    	call   DWORD PTR ds:0x58c1f0
  50f9d0:	50                   	push   eax
  50f9d1:	89 45 d4             	mov    DWORD PTR [ebp-0x2c],eax
  50f9d4:	ff 15 20 c2 58 00    	call   DWORD PTR ds:0x58c220
  50f9da:	8b 4d 0c             	mov    ecx,DWORD PTR [ebp+0xc]
  50f9dd:	83 c4 24             	add    esp,0x24
  50f9e0:	8b d1                	mov    edx,ecx
  50f9e2:	89 45 d8             	mov    DWORD PTR [ebp-0x28],eax
  50f9e5:	c6 06 00             	mov    BYTE PTR [esi],0x0
  50f9e8:	8d 7a 01             	lea    edi,[edx+0x1]
  50f9eb:	0f 1f 44 00 00       	nop    DWORD PTR [eax+eax*1+0x0]
  50f9f0:	8a 02                	mov    al,BYTE PTR [edx]
  50f9f2:	42                   	inc    edx
  50f9f3:	84 c0                	test   al,al
  50f9f5:	75 f9                	jne    0x50f9f0
  50f9f7:	2b d7                	sub    edx,edi
  50f9f9:	74 12                	je     0x50fa0d
  50f9fb:	8b d6                	mov    edx,esi
  50f9fd:	2b d1                	sub    edx,ecx
  50f9ff:	90                   	nop
  50fa00:	8a 01                	mov    al,BYTE PTR [ecx]
  50fa02:	8d 49 01             	lea    ecx,[ecx+0x1]
  50fa05:	88 44 0a ff          	mov    BYTE PTR [edx+ecx*1-0x1],al
  50fa09:	84 c0                	test   al,al
  50fa0b:	75 f3                	jne    0x50fa00
  50fa0d:	33 db                	xor    ebx,ebx
  50fa0f:	90                   	nop
  50fa10:	83 fb 1b             	cmp    ebx,0x1b
  50fa13:	0f 84 de 01 00 00    	je     0x50fbf7
  50fa19:	8b 5d d8             	mov    ebx,DWORD PTR [ebp-0x28]
  50fa1c:	68 ff 00 00 00       	push   0xff
  50fa21:	ff 75 16             	push   DWORD PTR [ebp+0x16]
  50fa24:	ff 75 15             	push   DWORD PTR [ebp+0x15]
  50fa27:	ff 75 14             	push   DWORD PTR [ebp+0x14]
  50fa2a:	53                   	push   ebx
  50fa2b:	ff 15 e4 c1 58 00    	call   DWORD PTR ds:0x58c1e4
  50fa31:	83 c4 14             	add    esp,0x14
  50fa34:	53                   	push   ebx
  50fa35:	ff 15 24 c2 58 00    	call   DWORD PTR ds:0x58c224
  50fa3b:	83 c4 04             	add    esp,0x4
  50fa3e:	ba 02 00 00 00       	mov    edx,0x2
  50fa43:	8b cb                	mov    ecx,ebx
  50fa45:	6a 00                	push   0x0
  50fa47:	ff 75 10             	push   DWORD PTR [ebp+0x10]
  50fa4a:	56                   	push   esi
  50fa4b:	6a 02                	push   0x2
  50fa4d:	e8 0e e8 ff ff       	call   0x50e260
  50fa52:	8b d6                	mov    edx,esi
  50fa54:	83 c4 10             	add    esp,0x10
  50fa57:	8d 4a 01             	lea    ecx,[edx+0x1]
  50fa5a:	66 0f 1f 44 00 00    	nop    WORD PTR [eax+eax*1+0x0]
  50fa60:	8a 02                	mov    al,BYTE PTR [edx]
  50fa62:	42                   	inc    edx
  50fa63:	84 c0                	test   al,al
  50fa65:	75 f9                	jne    0x50fa60
  50fa67:	6a 00                	push   0x0
  50fa69:	ff 75 10             	push   DWORD PTR [ebp+0x10]
  50fa6c:	2b d1                	sub    edx,ecx
  50fa6e:	8b cb                	mov    ecx,ebx
  50fa70:	68 04 c9 5a 00       	push   0x5ac904
  50fa75:	6a 02                	push   0x2
  50fa77:	8d 14 d5 02 00 00 00 	lea    edx,[edx*8+0x2]
  50fa7e:	e8 dd e7 ff ff       	call   0x50e260
  50fa83:	8b 45 cc             	mov    eax,DWORD PTR [ebp-0x34]
  50fa86:	8d 4d dc             	lea    ecx,[ebp-0x24]
  50fa89:	8b 5d d4             	mov    ebx,DWORD PTR [ebp-0x2c]
  50fa8c:	89 45 dc             	mov    DWORD PTR [ebp-0x24],eax
  50fa8f:	8b 45 c8             	mov    eax,DWORD PTR [ebp-0x38]
  50fa92:	83 c0 fe             	add    eax,0xfffffffe
  50fa95:	89 45 e0             	mov    DWORD PTR [ebp-0x20],eax
  50fa98:	8b 43 08             	mov    eax,DWORD PTR [ebx+0x8]
  50fa9b:	89 45 e4             	mov    DWORD PTR [ebp-0x1c],eax
  50fa9e:	8b 43 0c             	mov    eax,DWORD PTR [ebx+0xc]
  50faa1:	89 45 e8             	mov    DWORD PTR [ebp-0x18],eax
  50faa4:	e8 a7 e1 ff ff       	call   0x50dc50
  50faa9:	e8 d2 b9 ff ff       	call   0x50b480
  50faae:	53                   	push   ebx
  50faaf:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  50fab5:	ff 15 e0 c1 58 00    	call   DWORD PTR ds:0x58c1e0
  50fabb:	8b f8                	mov    edi,eax
  50fabd:	8d 45 dc             	lea    eax,[ebp-0x24]
  50fac0:	50                   	push   eax
  50fac1:	6a 00                	push   0x0
  50fac3:	57                   	push   edi
  50fac4:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  50faca:	ff 15 28 c2 58 00    	call   DWORD PTR ds:0x58c228
  50fad0:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  50fad6:	ff 15 6c c2 58 00    	call   DWORD PTR ds:0x58c26c
  50fadc:	83 c4 2c             	add    esp,0x2c
  50fadf:	85 c0                	test   eax,eax
  50fae1:	74 11                	je     0x50faf4
  50fae3:	6a 00                	push   0x0
  50fae5:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  50faeb:	ff 15 88 c2 58 00    	call   DWORD PTR ds:0x58c288
  50faf1:	83 c4 08             	add    esp,0x8
  50faf4:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  50fafa:	ff 15 7c c2 58 00    	call   DWORD PTR ds:0x58c27c
  50fb00:	83 c4 04             	add    esp,0x4
  50fb03:	57                   	push   edi
  50fb04:	ff 15 2c c2 58 00    	call   DWORD PTR ds:0x58c22c
  50fb0a:	83 c4 04             	add    esp,0x4
  50fb0d:	c7 05 34 56 35 06 01 	mov    DWORD PTR ds:0x6355634,0x1
  50fb14:	00 00 00 
  50fb17:	e8 d4 40 fc ff       	call   0x4d3bf0
  50fb1c:	8b d8                	mov    ebx,eax
  50fb1e:	8b 45 c4             	mov    eax,DWORD PTR [ebp-0x3c]
  50fb21:	a3 34 56 35 06       	mov    ds:0x6355634,eax
  50fb26:	83 fb d6             	cmp    ebx,0xffffffd6
  50fb29:	0f 84 bc 00 00 00    	je     0x50fbeb
  50fb2f:	81 fb 24 04 00 00    	cmp    ebx,0x424
  50fb35:	75 07                	jne    0x50fb3e
  50fb37:	bb 99 00 00 00       	mov    ebx,0x99
  50fb3c:	eb 46                	jmp    0x50fb84
  50fb3e:	81 fb 23 04 00 00    	cmp    ebx,0x423
  50fb44:	75 07                	jne    0x50fb4d
  50fb46:	bb 8e 00 00 00       	mov    ebx,0x8e
  50fb4b:	eb 37                	jmp    0x50fb84
  50fb4d:	83 fb 08             	cmp    ebx,0x8
  50fb50:	75 1d                	jne    0x50fb6f
  50fb52:	8b ce                	mov    ecx,esi
  50fb54:	8d 51 01             	lea    edx,[ecx+0x1]
  50fb57:	8a 01                	mov    al,BYTE PTR [ecx]
  50fb59:	41                   	inc    ecx
  50fb5a:	84 c0                	test   al,al
  50fb5c:	75 f9                	jne    0x50fb57
  50fb5e:	2b ca                	sub    ecx,edx
  50fb60:	0f 84 aa fe ff ff    	je     0x50fa10
  50fb66:	88 44 31 ff          	mov    BYTE PTR [ecx+esi*1-0x1],al
  50fb6a:	e9 a1 fe ff ff       	jmp    0x50fa10
  50fb6f:	83 fb 1b             	cmp    ebx,0x1b
  50fb72:	75 08                	jne    0x50fb7c
  50fb74:	66 89 1e             	mov    WORD PTR [esi],bx
  50fb77:	e9 94 fe ff ff       	jmp    0x50fa10
  50fb7c:	8d 43 e0             	lea    eax,[ebx-0x20]
  50fb7f:	83 f8 79             	cmp    eax,0x79
  50fb82:	77 5c                	ja     0x50fbe0
  50fb84:	8b ce                	mov    ecx,esi
  50fb86:	8d 51 01             	lea    edx,[ecx+0x1]
  50fb89:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [eax+0x0]
  50fb90:	8a 01                	mov    al,BYTE PTR [ecx]
  50fb92:	41                   	inc    ecx
  50fb93:	84 c0                	test   al,al
  50fb95:	75 f9                	jne    0x50fb90
  50fb97:	2b ca                	sub    ecx,edx
  50fb99:	83 f9 40             	cmp    ecx,0x40
  50fb9c:	73 42                	jae    0x50fbe0
  50fb9e:	53                   	push   ebx
  50fb9f:	8d 45 ec             	lea    eax,[ebp-0x14]
  50fba2:	68 dc d6 58 00       	push   0x58d6dc
  50fba7:	50                   	push   eax
  50fba8:	e8 23 15 ef ff       	call   0x4010d0
  50fbad:	8d 55 ec             	lea    edx,[ebp-0x14]
  50fbb0:	83 c4 0c             	add    esp,0xc
  50fbb3:	8b ca                	mov    ecx,edx
  50fbb5:	89 4d d0             	mov    DWORD PTR [ebp-0x30],ecx
  50fbb8:	8a 02                	mov    al,BYTE PTR [edx]
  50fbba:	42                   	inc    edx
  50fbbb:	84 c0                	test   al,al
  50fbbd:	75 f9                	jne    0x50fbb8
  50fbbf:	2b d1                	sub    edx,ecx
  50fbc1:	8d 7e ff             	lea    edi,[esi-0x1]
  50fbc4:	8a 47 01             	mov    al,BYTE PTR [edi+0x1]
  50fbc7:	47                   	inc    edi
  50fbc8:	84 c0                	test   al,al
  50fbca:	75 f8                	jne    0x50fbc4
  50fbcc:	8b 75 d0             	mov    esi,DWORD PTR [ebp-0x30]
  50fbcf:	8b ca                	mov    ecx,edx
  50fbd1:	c1 e9 02             	shr    ecx,0x2
  50fbd4:	f3 a5                	rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
  50fbd6:	8b ca                	mov    ecx,edx
  50fbd8:	83 e1 03             	and    ecx,0x3
  50fbdb:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
  50fbdd:	8b 75 c0             	mov    esi,DWORD PTR [ebp-0x40]
  50fbe0:	83 fb 0d             	cmp    ebx,0xd
  50fbe3:	0f 85 27 fe ff ff    	jne    0x50fa10
  50fbe9:	eb 0c                	jmp    0x50fbf7
  50fbeb:	c6 06 00             	mov    BYTE PTR [esi],0x0
  50fbee:	66 c7 06 1b 1b       	mov    WORD PTR [esi],0x1b1b
  50fbf3:	c6 46 02 00          	mov    BYTE PTR [esi+0x2],0x0
  50fbf7:	8b 45 d8             	mov    eax,DWORD PTR [ebp-0x28]
  50fbfa:	50                   	push   eax
  50fbfb:	ff 15 18 c2 58 00    	call   DWORD PTR ds:0x58c218
  50fc01:	8b 45 d4             	mov    eax,DWORD PTR [ebp-0x2c]
  50fc04:	83 c4 04             	add    esp,0x4
  50fc07:	50                   	push   eax
  50fc08:	ff 15 f4 c1 58 00    	call   DWORD PTR ds:0x58c1f4
  50fc0e:	8b 4d f8             	mov    ecx,DWORD PTR [ebp-0x8]
  50fc11:	83 c4 04             	add    esp,0x4
  50fc14:	8b c6                	mov    eax,esi
  50fc16:	33 cd                	xor    ecx,ebp
  50fc18:	5f                   	pop    edi
  50fc19:	5e                   	pop    esi
  50fc1a:	5b                   	pop    ebx
  50fc1b:	e8 8e a4 07 00       	call   0x58a0ae
  50fc20:	8b e5                	mov    esp,ebp
  50fc22:	5d                   	pop    ebp
  50fc23:	c3                   	ret

/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

004e47b6 <.text+0xe37b6>:
  4e47b6:	8b 15 e4 10 61 0a    	mov    edx,DWORD PTR ds:0xa6110e4
  4e47bc:	51                   	push   ecx
  4e47bd:	ff 35 60 ef 58 00    	push   DWORD PTR ds:0x58ef60
  4e47c3:	ff 35 ac 87 5e 00    	push   DWORD PTR ds:0x5e87ac
  4e47c9:	80 fb 02             	cmp    bl,0x2
  4e47cc:	74 30                	je     0x4e47fe
  4e47ce:	8d 85 e0 f5 ff ff    	lea    eax,[ebp-0xa20]
  4e47d4:	50                   	push   eax
  4e47d5:	51                   	push   ecx
  4e47d6:	8b 0d e0 10 61 0a    	mov    ecx,DWORD PTR ds:0xa6110e0
  4e47dc:	8d 52 1e             	lea    edx,[edx+0x1e]
  4e47df:	8d 49 1e             	lea    ecx,[ecx+0x1e]
  4e47e2:	e8 69 b1 02 00       	call   0x50f950
  4e47e7:	8d 95 90 fb ff ff    	lea    edx,[ebp-0x470]
  4e47ed:	83 c4 14             	add    esp,0x14
  4e47f0:	2b d0                	sub    edx,eax
  4e47f2:	8a 08                	mov    cl,BYTE PTR [eax]
  4e47f4:	88 0c 02             	mov    BYTE PTR [edx+eax*1],cl
  4e47f7:	40                   	inc    eax
  4e47f8:	84 c9                	test   cl,cl
  4e47fa:	75 f6                	jne    0x4e47f2
  4e47fc:	eb 2e                	jmp    0x4e482c
  4e47fe:	8d 85 44 f6 ff ff    	lea    eax,[ebp-0x9bc]
  4e4804:	50                   	push   eax
  4e4805:	51                   	push   ecx
  4e4806:	8b 0d e0 10 61 0a    	mov    ecx,DWORD PTR ds:0xa6110e0
  4e480c:	8d 52 2d             	lea    edx,[edx+0x2d]
  4e480f:	8d 49 1e             	lea    ecx,[ecx+0x1e]
  4e4812:	e8 39 b1 02 00       	call   0x50f950
  4e4817:	8d 95 90 fb ff ff    	lea    edx,[ebp-0x470]
  4e481d:	83 c4 14             	add    esp,0x14
  4e4820:	2b d0                	sub    edx,eax
  4e4822:	8a 08                	mov    cl,BYTE PTR [eax]
  4e4824:	88 0c 02             	mov    BYTE PTR [edx+eax*1],cl
  4e4827:	40                   	inc    eax
  4e4828:	84 c9                	test   cl,cl
  4e482a:	75 f6                	jne    0x4e4822
  4e482c:	80 bd 90 fb ff ff 1b 	cmp    BYTE PTR [ebp-0x470],0x1b
  4e4833:	75 36                	jne    0x4e486b
  4e4835:	80 bd 91 fb ff ff 1b 	cmp    BYTE PTR [ebp-0x46f],0x1b
  4e483c:	bf 01 00 00 00       	mov    edi,0x1
  4e4841:	8b 8d c4 f5 ff ff    	mov    ecx,DWORD PTR [ebp-0xa3c]
  4e4847:	0f 44 cf             	cmove  ecx,edi
  4e484a:	32 c0                	xor    al,al
  4e484c:	89 8d c4 f5 ff ff    	mov    DWORD PTR [ebp-0xa3c],ecx
  4e4852:	88 85 ce f5 ff ff    	mov    BYTE PTR [ebp-0xa32],al
  4e4858:	85 c9                	test   ecx,ecx
  4e485a:	0f 85 ac fe ff ff    	jne    0x4e470c
  4e4860:	8a 9d cf f5 ff ff    	mov    bl,BYTE PTR [ebp-0xa31]
  4e4866:	e9 db f8 ff ff       	jmp    0x4e4146
  4e486b:	33 c9                	xor    ecx,ecx
  4e486d:	80 fb 02             	cmp    bl,0x2

/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

004e1340 <.text+0xe0340>:
  4e1340:	55                   	push   ebp
  4e1341:	8b ec                	mov    ebp,esp
  4e1343:	b8 74 13 00 00       	mov    eax,0x1374
  4e1348:	e8 83 9d 0a 00       	call   0x58b0d0
  4e134d:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  4e1352:	33 c5                	xor    eax,ebp
  4e1354:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  4e1357:	53                   	push   ebx
  4e1358:	56                   	push   esi
  4e1359:	57                   	push   edi
  4e135a:	8a f9                	mov    bh,cl
  4e135c:	8d 75 08             	lea    esi,[ebp+0x8]
  4e135f:	b9 6c 01 00 00       	mov    ecx,0x16c
  4e1364:	88 bd 97 ec ff ff    	mov    BYTE PTR [ebp-0x1369],bh
  4e136a:	8d bd 48 f2 ff ff    	lea    edi,[ebp-0xdb8]
  4e1370:	f3 a5                	rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
  4e1372:	8b 85 48 f2 ff ff    	mov    eax,DWORD PTR [ebp-0xdb8]
  4e1378:	89 85 8c ec ff ff    	mov    DWORD PTR [ebp-0x1374],eax
  4e137e:	8b 85 4c f2 ff ff    	mov    eax,DWORD PTR [ebp-0xdb4]
  4e1384:	68 00 04 00 00       	push   0x400
  4e1389:	89 85 90 ec ff ff    	mov    DWORD PTR [ebp-0x1370],eax
  4e138f:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  4e1395:	6a 00                	push   0x0
  4e1397:	50                   	push   eax
  4e1398:	e8 c3 9a 0a 00       	call   0x58ae60
  4e139d:	83 c4 0c             	add    esp,0xc
  4e13a0:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  4e13a6:	68 90 3c 78 0a       	push   0xa783c90
  4e13ab:	68 ac 68 5a 00       	push   0x5a68ac
  4e13b0:	50                   	push   eax
  4e13b1:	e8 1a fd f1 ff       	call   0x4010d0
  4e13b6:	8b 3d 78 c4 58 00    	mov    edi,DWORD PTR ds:0x58c478
  4e13bc:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  4e13c2:	83 c4 0c             	add    esp,0xc
  4e13c5:	68 0c f2 58 00       	push   0x58f20c
  4e13ca:	50                   	push   eax
  4e13cb:	ff d7                	call   edi
  4e13cd:	8b f0                	mov    esi,eax
  4e13cf:	83 c4 08             	add    esp,0x8
  4e13d2:	85 f6                	test   esi,esi
  4e13d4:	75 10                	jne    0x4e13e6
  4e13d6:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  4e13dc:	68 78 f9 58 00       	push   0x58f978
  4e13e1:	50                   	push   eax
  4e13e2:	ff d7                	call   edi
  4e13e4:	eb 7f                	jmp    0x4e1465
  4e13e6:	8b 1d e0 c4 58 00    	mov    ebx,DWORD PTR ds:0x58c4e0
  4e13ec:	33 ff                	xor    edi,edi
  4e13ee:	56                   	push   esi
  4e13ef:	ff d3                	call   ebx
  4e13f1:	83 c4 04             	add    esp,0x4
  4e13f4:	85 c0                	test   eax,eax
  4e13f6:	75 4b                	jne    0x4e1443
  4e13f8:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [eax+eax*1+0x0]
  4e13ff:	00 
  4e1400:	56                   	push   esi
  4e1401:	6a 01                	push   0x1
  4e1403:	8d 85 98 ec ff ff    	lea    eax,[ebp-0x1368]
  4e1409:	68 b0 05 00 00       	push   0x5b0
  4e140e:	50                   	push   eax
  4e140f:	ff 15 a8 c4 58 00    	call   DWORD PTR ds:0x58c4a8
  4e1415:	8b 85 98 ec ff ff    	mov    eax,DWORD PTR [ebp-0x1368]
  4e141b:	83 c4 10             	add    esp,0x10
  4e141e:	3b 85 48 f2 ff ff    	cmp    eax,DWORD PTR [ebp-0xdb8]
  4e1424:	75 12                	jne    0x4e1438
  4e1426:	8b 85 9c ec ff ff    	mov    eax,DWORD PTR [ebp-0x1364]
  4e142c:	3b 85 4c f2 ff ff    	cmp    eax,DWORD PTR [ebp-0xdb4]
  4e1432:	0f 84 94 00 00 00    	je     0x4e14cc
  4e1438:	56                   	push   esi
  4e1439:	47                   	inc    edi
  4e143a:	ff d3                	call   ebx
  4e143c:	83 c4 04             	add    esp,0x4
  4e143f:	85 c0                	test   eax,eax
  4e1441:	74 bd                	je     0x4e1400
  4e1443:	8a bd 97 ec ff ff    	mov    bh,BYTE PTR [ebp-0x1369]
  4e1449:	56                   	push   esi
  4e144a:	ff 15 b4 c4 58 00    	call   DWORD PTR ds:0x58c4b4
  4e1450:	83 c4 04             	add    esp,0x4
  4e1453:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  4e1459:	68 34 21 59 00       	push   0x592134
  4e145e:	50                   	push   eax
  4e145f:	ff 15 78 c4 58 00    	call   DWORD PTR ds:0x58c478
  4e1465:	8b f0                	mov    esi,eax
  4e1467:	83 c4 08             	add    esp,0x8
  4e146a:	8b 3d d8 c4 58 00    	mov    edi,DWORD PTR ds:0x58c4d8
  4e1470:	8d 85 48 f2 ff ff    	lea    eax,[ebp-0xdb8]
  4e1476:	56                   	push   esi
  4e1477:	6a 01                	push   0x1
  4e1479:	68 b0 05 00 00       	push   0x5b0
  4e147e:	50                   	push   eax
  4e147f:	ff d7                	call   edi
  4e1481:	56                   	push   esi
  4e1482:	ff 15 b4 c4 58 00    	call   DWORD PTR ds:0x58c4b4
  4e1488:	83 c4 14             	add    esp,0x14
  4e148b:	32 db                	xor    bl,bl
  4e148d:	e8 7e cc fa ff       	call   0x48e110
  4e1492:	8a 95 50 f2 ff ff    	mov    dl,BYTE PTR [ebp-0xdb0]
  4e1498:	b9 d0 bd 72 0a       	mov    ecx,0xa72bdd0
  4e149d:	8b b5 8c ec ff ff    	mov    esi,DWORD PTR [ebp-0x1374]
  4e14a3:	80 79 04 0d          	cmp    BYTE PTR [ecx+0x4],0xd
  4e14a7:	75 7d                	jne    0x4e1526
  4e14a9:	0f b7 01             	movzx  eax,WORD PTR [ecx]
  4e14ac:	3b c6                	cmp    eax,esi
  4e14ae:	75 76                	jne    0x4e1526
  4e14b0:	0f b7 41 02          	movzx  eax,WORD PTR [ecx+0x2]
  4e14b4:	3b 85 90 ec ff ff    	cmp    eax,DWORD PTR [ebp-0x1370]
  4e14ba:	75 6a                	jne    0x4e1526
  4e14bc:	b3 01                	mov    bl,0x1
  4e14be:	84 ff                	test   bh,bh
  4e14c0:	74 5e                	je     0x4e1520
  4e14c2:	33 c0                	xor    eax,eax
  4e14c4:	c6 41 04 21          	mov    BYTE PTR [ecx+0x4],0x21
  4e14c8:	89 01                	mov    DWORD PTR [ecx],eax
  4e14ca:	eb 5a                	jmp    0x4e1526
  4e14cc:	8a bd 97 ec ff ff    	mov    bh,BYTE PTR [ebp-0x1369]
  4e14d2:	84 ff                	test   bh,bh
  4e14d4:	74 2a                	je     0x4e1500
  4e14d6:	68 b0 05 00 00       	push   0x5b0
  4e14db:	8d 85 48 f2 ff ff    	lea    eax,[ebp-0xdb8]
  4e14e1:	6a 00                	push   0x0
  4e14e3:	50                   	push   eax
  4e14e4:	e8 77 99 0a 00       	call   0x58ae60
  4e14e9:	83 c4 0c             	add    esp,0xc
  4e14ec:	c7 85 48 f2 ff ff 00 	mov    DWORD PTR [ebp-0xdb8],0x0
  4e14f3:	00 00 00 
  4e14f6:	c7 85 4c f2 ff ff 00 	mov    DWORD PTR [ebp-0xdb4],0x0
  4e14fd:	00 00 00 
  4e1500:	85 ff                	test   edi,edi
  4e1502:	0f 88 41 ff ff ff    	js     0x4e1449
  4e1508:	69 c7 b0 05 00 00    	imul   eax,edi,0x5b0
  4e150e:	6a 00                	push   0x0
  4e1510:	50                   	push   eax
  4e1511:	56                   	push   esi
  4e1512:	ff 15 bc c4 58 00    	call   DWORD PTR ds:0x58c4bc
  4e1518:	83 c4 0c             	add    esp,0xc
  4e151b:	e9 4a ff ff ff       	jmp    0x4e146a
  4e1520:	0f b6 c2             	movzx  eax,dl
  4e1523:	89 41 0c             	mov    DWORD PTR [ecx+0xc],eax
  4e1526:	83 c1 24             	add    ecx,0x24
  4e1529:	81 f9 10 3c 78 0a    	cmp    ecx,0xa783c10
  4e152f:	0f                   	.byte 0xf
