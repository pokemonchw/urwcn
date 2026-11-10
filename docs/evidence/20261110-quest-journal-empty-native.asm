; Static excerpts from windows-3891-native-full.asm, original PE image base 00400000.
; Native file analysis only. No game, product or tests executed.
; PE jump table RVA 115E3C, indexed by mode-1: mode 5 -> RVA 115B24.
  513550:	51                   	push   ecx
  513551:	56                   	push   esi
  513552:	57                   	push   edi
  513553:	ff 35 f4 0e 62 0a    	push   DWORD PTR ds:0xa620ef4
  513559:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  51355f:	ff 15 88 c2 58 00    	call   DWORD PTR ds:0x58c288
  513565:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  51356a:	8b 3d cc 10 61 0a    	mov    edi,DWORD PTR ds:0xa6110cc
  513570:	8b 35 98 87 5e 00    	mov    esi,DWORD PTR ds:0x5e8798
  513576:	6a 54                	push   0x54
  513578:	68 fc 00 00 00       	push   0xfc
  51357d:	68 fc 00 00 00       	push   0xfc
  513582:	ff 70 04             	push   DWORD PTR [eax+0x4]
  513585:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  51358b:	ff 35 2c ef 58 00    	push   DWORD PTR ds:0x58ef2c
  513591:	ba 05 00 00 00       	mov    edx,0x5
  513596:	8b cf                	mov    ecx,edi
  513598:	68 00 10 00 00       	push   0x1000
  51359d:	68 16 c6 58 00       	push   0x58c616
  5135a2:	6a 10                	push   0x10
  5135a4:	68 16 03 00 00       	push   0x316
  5135a9:	6a 05                	push   0x5
  5135ab:	e8 10 31 00 00       	call   0x5166c0
  5135b0:	6a 01                	push   0x1
  5135b2:	56                   	push   esi
  5135b3:	68 f8 c6 5c 00       	push   0x5cc6f8
  5135b8:	6a 09                	push   0x9
  5135ba:	ba 5c 01 00 00       	mov    edx,0x15c
  5135bf:	8b cf                	mov    ecx,edi
  5135c1:	e8 9a ac ff ff       	call   0x50e260
  5135c6:	83 c4 40             	add    esp,0x40
  5135c9:	6a 00                	push   0x0
  5135cb:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  5135d1:	ff 15 88 c2 58 00    	call   DWORD PTR ds:0x58c288
  5135d7:	83 c4 08             	add    esp,0x8
  5135da:	5f                   	pop    edi
  5135db:	5e                   	pop    esi
  5135dc:	59                   	pop    ecx
  5135dd:	c3                   	ret
  515ad0:	55                   	push   ebp
  515ad1:	8b ec                	mov    ebp,esp
  515ad3:	83 ec 0c             	sub    esp,0xc
  515ad6:	53                   	push   ebx
  515ad7:	8b 5d 08             	mov    ebx,DWORD PTR [ebp+0x8]
  515ada:	56                   	push   esi
  515adb:	8b 35 98 87 5e 00    	mov    esi,DWORD PTR ds:0x5e8798
  515ae1:	57                   	push   edi
  515ae2:	8b fa                	mov    edi,edx
  515ae4:	89 4d fc             	mov    DWORD PTR [ebp-0x4],ecx
  515ae7:	6a 54                	push   0x54
  515ae9:	68 fc 00 00 00       	push   0xfc
  515aee:	68 fc 00 00 00       	push   0xfc
  515af3:	8d 47 05             	lea    eax,[edi+0x5]
  515af6:	89 45 f8             	mov    DWORD PTR [ebp-0x8],eax
  515af9:	8d 43 04             	lea    eax,[ebx+0x4]
  515afc:	89 45 08             	mov    DWORD PTR [ebp+0x8],eax
  515aff:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  515b04:	ff 70 04             	push   DWORD PTR [eax+0x4]
  515b07:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  515b0d:	8b 45 14             	mov    eax,DWORD PTR [ebp+0x14]
  515b10:	83 c4 10             	add    esp,0x10
  515b13:	48                   	dec    eax
  515b14:	83 f8 0a             	cmp    eax,0xa
  515b17:	0f 87 5b 02 00 00    	ja     0x515d78
  515b1d:	ff 24 85 3c 5e 51 00 	jmp    DWORD PTR [eax*4+0x515e3c]
  515b24:	ff 35 2c ef 58 00    	push   DWORD PTR ds:0x58ef2c
  515b2a:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  515b2d:	8b d7                	mov    edx,edi
  515b2f:	68 00 10 00 00       	push   0x1000
  515b34:	68 16 c6 58 00       	push   0x58c616
  515b39:	6a 10                	push   0x10
  515b3b:	ff 75 0c             	push   DWORD PTR [ebp+0xc]
  515b3e:	53                   	push   ebx
  515b3f:	e8 7c 0b 00 00       	call   0x5166c0
  515b44:	8b 5d 10             	mov    ebx,DWORD PTR [ebp+0x10]
  515b47:	83 c4 18             	add    esp,0x18
  515b4a:	8b cb                	mov    ecx,ebx
  515b4c:	8d 51 01             	lea    edx,[ecx+0x1]
  515b4f:	90                   	nop
  515b50:	8a 01                	mov    al,BYTE PTR [ecx]
  515b52:	41                   	inc    ecx
  515b53:	84 c0                	test   al,al
  515b55:	75 f9                	jne    0x515b50
  515b57:	2b ca                	sub    ecx,edx
  515b59:	8d 04 cd 00 00 00 00 	lea    eax,[ecx*8+0x0]
  515b60:	99                   	cdq
  515b61:	2b c2                	sub    eax,edx
  515b63:	8b c8                	mov    ecx,eax
  515b65:	8b 45 0c             	mov    eax,DWORD PTR [ebp+0xc]
  515b68:	99                   	cdq
  515b69:	2b c2                	sub    eax,edx
  515b6b:	d1 f9                	sar    ecx,1
  515b6d:	d1 f8                	sar    eax,1
  515b6f:	2b c1                	sub    eax,ecx
  515b71:	03 c7                	add    eax,edi
  515b73:	e9 a8 02 00 00       	jmp    0x515e20
  515e1a:	8b 5d 10             	mov    ebx,DWORD PTR [ebp+0x10]
  515e1d:	8b 45 f8             	mov    eax,DWORD PTR [ebp-0x8]
  515e20:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  515e23:	8b d0                	mov    edx,eax
  515e25:	6a 01                	push   0x1
  515e27:	56                   	push   esi
  515e28:	53                   	push   ebx
  515e29:	ff 75 08             	push   DWORD PTR [ebp+0x8]
  515e2c:	e8 2f 84 ff ff       	call   0x50e260
  515e31:	83 c4 10             	add    esp,0x10
  515e34:	5f                   	pop    edi
  557d75:	a1 f4 0e 62 0a       	mov    eax,ds:0xa620ef4
  557d7a:	66 0f 1f 44 00 00    	nop    WORD PTR [eax+eax*1+0x0]
  557d80:	85 c9                	test   ecx,ecx
  557d82:	74 5e                	je     0x557de2
  557d84:	85 c0                	test   eax,eax
  557d86:	74 0a                	je     0x557d92
  557d88:	50                   	push   eax
  557d89:	ff 15 2c c2 58 00    	call   DWORD PTR ds:0x58c22c
  557d8f:	83 c4 04             	add    esp,0x4
  557d92:	68 58 02 00 00       	push   0x258
  557d97:	68 20 03 00 00       	push   0x320
  557d9c:	6a 02                	push   0x2
  557d9e:	68 04 20 36 16       	push   0x16362004
  557da3:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  557da9:	ff 15 08 c2 58 00    	call   DWORD PTR ds:0x58c208
  557daf:	8b 15 c8 10 61 0a    	mov    edx,DWORD PTR ds:0xa6110c8
  557db5:	83 c4 10             	add    esp,0x10
  557db8:	a3 f4 0e 62 0a       	mov    ds:0xa620ef4,eax
  557dbd:	68 58 02 00 00       	push   0x258
  557dc2:	68 20 03 00 00       	push   0x320
  557dc7:	83 ec 08             	sub    esp,0x8
  557dca:	50                   	push   eax
  557dcb:	e8 c0 b2 fb ff       	call   0x513090
  557dd0:	83 c4 18             	add    esp,0x18
  557dd3:	e8 78 b7 fb ff       	call   0x513550
  557dd8:	b9 d8 c6 5c 00       	mov    ecx,0x5cc6d8
  557ddd:	e8 6e 34 fb ff       	call   0x50b250
  558d3f:	8b 35 88 c2 58 00    	mov    esi,DWORD PTR ds:0x58c288
  558d45:	a1 f4 0e 62 0a       	mov    eax,ds:0xa620ef4
  558d4a:	85 c0                	test   eax,eax
  558d4c:	74 0a                	je     0x558d58
  558d4e:	50                   	push   eax
  558d4f:	ff 15 2c c2 58 00    	call   DWORD PTR ds:0x58c22c
  558d55:	83 c4 04             	add    esp,0x4
  558d58:	68 58 02 00 00       	push   0x258
  558d5d:	68 20 03 00 00       	push   0x320
  558d62:	6a 02                	push   0x2
  558d64:	68 04 20 36 16       	push   0x16362004
  558d69:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  558d6f:	ff 15 08 c2 58 00    	call   DWORD PTR ds:0x58c208
  558d75:	8b 15 c8 10 61 0a    	mov    edx,DWORD PTR ds:0xa6110c8
  558d7b:	83 c4 10             	add    esp,0x10
  558d7e:	a3 f4 0e 62 0a       	mov    ds:0xa620ef4,eax
  558d83:	68 58 02 00 00       	push   0x258
  558d88:	68 20 03 00 00       	push   0x320
  558d8d:	83 ec 08             	sub    esp,0x8
  558d90:	50                   	push   eax
  558d91:	e8 fa a2 fb ff       	call   0x513090
  558d96:	83 c4 18             	add    esp,0x18
  558d99:	e8 b2 a7 fb ff       	call   0x513550
  558d9e:	b9 16 c6 58 00       	mov    ecx,0x58c616
  558da3:	e8 f8 f9 ff ff       	call   0x5587a0
  558da8:	8b 1d f4 0e 62 0a    	mov    ebx,DWORD PTR ds:0xa620ef4
  558dae:	89 85 d4 fb ff ff    	mov    DWORD PTR [ebp-0x42c],eax
  558db4:	89 1d bc 1c 5c 0a    	mov    DWORD PTR ds:0xa5c1cbc,ebx
  558dba:	c7 05 10 20 5c 0a 10 	mov    DWORD PTR ds:0xa5c2010,0x10
  558dc1:	00 00 00 
  558dc4:	85 c0                	test   eax,eax
  558dc6:	0f 84 84 04 00 00    	je     0x559250
  559250:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  559256:	8b 35 60 ef 58 00    	mov    esi,DWORD PTR ds:0x58ef60
  55925c:	ff 15 6c c2 58 00    	call   DWORD PTR ds:0x58c26c
  559262:	83 c4 04             	add    esp,0x4
  559265:	8b f8                	mov    edi,eax
  559267:	53                   	push   ebx
  559268:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  55926e:	8b 1d 88 c2 58 00    	mov    ebx,DWORD PTR ds:0x58c288
  559274:	ff d3                	call   ebx
  559276:	8b 0d cc 10 61 0a    	mov    ecx,DWORD PTR ds:0xa6110cc
  55927c:	ba 0a 00 00 00       	mov    edx,0xa
  559281:	6a 00                	push   0x0
  559283:	56                   	push   esi
  559284:	68 58 c8 5c 00       	push   0x5cc858
  559289:	6a 1e                	push   0x1e
  55928b:	e8 d0 4f fb ff       	call   0x50e260
  559290:	57                   	push   edi
  559291:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  559297:	ff d3                	call   ebx
  559299:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  55929f:	8b 35 60 ef 58 00    	mov    esi,DWORD PTR ds:0x58ef60
  5592a5:	8b 3d f4 0e 62 0a    	mov    edi,DWORD PTR ds:0xa620ef4
  5592ab:	ff 15 6c c2 58 00    	call   DWORD PTR ds:0x58c26c
  5592b1:	83 c4 24             	add    esp,0x24
  5592b4:	8b d8                	mov    ebx,eax
  5592b6:	57                   	push   edi
  5592b7:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  5592bd:	8b 3d 88 c2 58 00    	mov    edi,DWORD PTR ds:0x58c288
  5592c3:	ff d7                	call   edi
  5592c5:	8b 0d cc 10 61 0a    	mov    ecx,DWORD PTR ds:0xa6110cc
  5592cb:	ba 0a 00 00 00       	mov    edx,0xa
  5592d0:	6a 00                	push   0x0
  5592d2:	56                   	push   esi
  5592d3:	68 88 c8 5c 00       	push   0x5cc888
  5592d8:	6a 28                	push   0x28
  5592da:	e8 81 4f fb ff       	call   0x50e260
  5592df:	53                   	push   ebx
  5592e0:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  5592e6:	ff d7                	call   edi
  5592e8:	e8 93 21 fb ff       	call   0x50b480
  5592ed:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  5592f3:	ff 15 6c c2 58 00    	call   DWORD PTR ds:0x58c26c
  5592f9:	83 c4 24             	add    esp,0x24
  5592fc:	85 c0                	test   eax,eax
  5592fe:	74 0d                	je     0x55930d
  559300:	6a 00                	push   0x0
  559302:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  559308:	ff d7                	call   edi
  55930a:	83 c4 08             	add    esp,0x8
  55930d:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  559313:	ff 15 7c c2 58 00    	call   DWORD PTR ds:0x58c27c
  559319:	83 c4 04             	add    esp,0x4
  55931c:	c7 05 5c ba 5b 06 01 	mov    DWORD PTR ds:0x65bba5c,0x1
  559323:	00 00 00 
  559326:	c7 05 34 56 35 06 01 	mov    DWORD PTR ds:0x6355634,0x1
  55932d:	00 00 00 
  559330:	e8 4b a9 f7 ff       	call   0x4d3c80
  559335:	c7 05 5c ba 5b 06 00 	mov    DWORD PTR ds:0x65bba5c,0x0
  55933c:	00 00 00 
