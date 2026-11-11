
/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

004fe2b0 <.text+0xfd2b0>:
  4fe2b0:	55                   	push   ebp
  4fe2b1:	8b ec                	mov    ebp,esp
  4fe2b3:	83 e4 f8             	and    esp,0xfffffff8
  4fe2b6:	81 ec 4c 0d 00 00    	sub    esp,0xd4c
  4fe2bc:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  4fe2c1:	33 c4                	xor    eax,esp
  4fe2c3:	89 84 24 48 0d 00 00 	mov    DWORD PTR [esp+0xd48],eax
  4fe2ca:	53                   	push   ebx
  4fe2cb:	33 db                	xor    ebx,ebx
  4fe2cd:	c7 44 24 10 00 00 00 	mov    DWORD PTR [esp+0x10],0x0
  4fe2d4:	00 
  4fe2d5:	56                   	push   esi
  4fe2d6:	57                   	push   edi
  4fe2d7:	c7 44 24 1c 00 00 00 	mov    DWORD PTR [esp+0x1c],0x0
  4fe2de:	00 
  4fe2df:	33 d2                	xor    edx,edx
  4fe2e1:	c7 44 24 20 00 00 00 	mov    DWORD PTR [esp+0x20],0x0
  4fe2e8:	00 
  4fe2e9:	b9 2c 52 78 0a       	mov    ecx,0xa78522c
  4fe2ee:	89 5c 24 10          	mov    DWORD PTR [esp+0x10],ebx
  4fe2f2:	8a 01                	mov    al,BYTE PTR [ecx]
  4fe2f4:	8d 52 01             	lea    edx,[edx+0x1]
  4fe2f7:	81 c1 48 0c 00 00    	add    ecx,0xc48
  4fe2fd:	88 82 6f ef 80 0a    	mov    BYTE PTR [edx+0xa80ef6f],al
  4fe303:	81 f9 2c 76 7e 0a    	cmp    ecx,0xa7e762c
  4fe309:	7c e7                	jl     0x4fe2f2
  4fe30b:	b9 5c 41 59 00       	mov    ecx,0x59415c
  4fe310:	e8 db cd 00 00       	call   0x50b0f0
  4fe315:	66 66 66 0f 1f 84 00 	data16 data16 nop WORD PTR [eax+eax*1+0x0]
  4fe31c:	00 00 00 00 
  4fe320:	68 90 3c 78 0a       	push   0xa783c90
  4fe325:	8d 84 24 54 01 00 00 	lea    eax,[esp+0x154]
  4fe32c:	33 f6                	xor    esi,esi
  4fe32e:	68 58 65 5a 00       	push   0x5a6558
  4fe333:	50                   	push   eax
  4fe334:	89 74 24 20          	mov    DWORD PTR [esp+0x20],esi
  4fe338:	e8 93 2d f0 ff       	call   0x4010d0
  4fe33d:	83 c4 0c             	add    esp,0xc
  4fe340:	8d 84 24 50 01 00 00 	lea    eax,[esp+0x150]
  4fe347:	68 08 f7 58 00       	push   0x58f708
  4fe34c:	50                   	push   eax
  4fe34d:	ff 15 78 c4 58 00    	call   DWORD PTR ds:0x58c478
  4fe353:	8b d8                	mov    ebx,eax
  4fe355:	83 c4 08             	add    esp,0x8
  4fe358:	85 db                	test   ebx,ebx
  4fe35a:	0f 84 ce 0a 00 00    	je     0x4fee2e
  4fe360:	0f 28 05 e0 da 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5ddae0
  4fe367:	33 c0                	xor    eax,eax
  4fe369:	68 58 1b 00 00       	push   0x1b58
  4fe36e:	50                   	push   eax
  4fe36f:	b9 46 00 00 00       	mov    ecx,0x46
  4fe374:	c7 05 a8 9d 5a 06 01 	mov    DWORD PTR ds:0x65a9da8,0x1010101
  4fe37b:	01 01 01 
  4fe37e:	bf a0 9a 5a 06       	mov    edi,0x65a9aa0
  4fe383:	66 c7 05 ac 9d 5a 06 	mov    WORD PTR ds:0x65a9dac,0x101
  4fe38a:	01 01 
  4fe38c:	f3 ab                	rep stos DWORD PTR es:[edi],eax
  4fe38e:	68 90 61 5a 06       	push   0x65a6190
  4fe393:	0f 11 05 68 9d 5a 06 	movups XMMWORD PTR ds:0x65a9d68,xmm0
  4fe39a:	0f 11 05 78 9d 5a 06 	movups XMMWORD PTR ds:0x65a9d78,xmm0
  4fe3a1:	0f 11 05 88 9d 5a 06 	movups XMMWORD PTR ds:0x65a9d88,xmm0
  4fe3a8:	0f 11 05 98 9d 5a 06 	movups XMMWORD PTR ds:0x65a9d98,xmm0
  4fe3af:	e8 ac ca 08 00       	call   0x58ae60
  4fe3b4:	83 c4 0c             	add    esp,0xc
  4fe3b7:	68 00 18 01 00       	push   0x11800
  4fe3bc:	56                   	push   esi
  4fe3bd:	68 b0 9d 5a 06       	push   0x65a9db0
  4fe3c2:	e8 99 ca 08 00       	call   0x58ae60
  4fe3c7:	66 0f 6e 0d bc 6a 5e 	movd   xmm1,DWORD PTR ds:0x5e6abc
  4fe3ce:	00 
  4fe3cf:	b8 58 02 00 00       	mov    eax,0x258
  4fe3d4:	0f 5b c9             	cvtdq2ps xmm1,xmm1
  4fe3d7:	33 d2                	xor    edx,edx
  4fe3d9:	89 35 d8 bc 5b 06    	mov    DWORD PTR ds:0x65bbcd8,esi
  4fe3df:	83 c4 0c             	add    esp,0xc
  4fe3e2:	33 ff                	xor    edi,edi
  4fe3e4:	0f 28 c1             	movaps xmm0,xmm1
  4fe3e7:	f3 0f 59 05 4c d5 5d 	mulss  xmm0,DWORD PTR ds:0x5dd54c
  4fe3ee:	00 
  4fe3ef:	f3 0f 2c c8          	cvttss2si ecx,xmm0
  4fe3f3:	2b c1                	sub    eax,ecx
  4fe3f5:	f3 0f 2c c9          	cvttss2si ecx,xmm1
  4fe3f9:	f7 f1                	div    ecx
  4fe3fb:	b9 7c d5 59 00       	mov    ecx,0x59d57c
  4fe400:	89 44 24 28          	mov    DWORD PTR [esp+0x28],eax
  4fe404:	e8 e7 cc 00 00       	call   0x50b0f0
  4fe409:	39 35 fc ba 5b 06    	cmp    DWORD PTR ds:0x65bbafc,esi
  4fe40f:	75 31                	jne    0x4fe442
  4fe411:	0f 28 05 c0 da 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5ddac0
  4fe418:	8d 44 24 48          	lea    eax,[esp+0x48]
  4fe41c:	50                   	push   eax
  4fe41d:	ff 35 24 bd 5b 0a    	push   DWORD PTR ds:0xa5bbd24
  4fe423:	0f 11 44 24 50       	movups XMMWORD PTR [esp+0x50],xmm0
  4fe428:	50                   	push   eax
  4fe429:	ff 35 10 bb 5b 06    	push   DWORD PTR ds:0x65bbb10
  4fe42f:	ff 15 04 c2 58 00    	call   DWORD PTR ds:0x58c204
  4fe435:	83 c4 10             	add    esp,0x10
  4fe438:	c7 05 fc ba 5b 06 01 	mov    DWORD PTR ds:0x65bbafc,0x1
  4fe43f:	00 00 00 
  4fe442:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4fe447:	68 99 00 00 00       	push   0x99
  4fe44c:	68 c5 00 00 00       	push   0xc5
  4fe451:	68 e2 00 00 00       	push   0xe2
  4fe456:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fe459:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  4fe45f:	50                   	push   eax
  4fe460:	68 00 10 00 00       	push   0x1000
  4fe465:	68 24 ac 5a 00       	push   0x5aac24
  4fe46a:	68 58 02 00 00       	push   0x258
  4fe46f:	68 20 03 00 00       	push   0x320
  4fe474:	33 d2                	xor    edx,edx
  4fe476:	33 c9                	xor    ecx,ecx
  4fe478:	e8 f3 7d 01 00       	call   0x516270
  4fe47d:	83 c4 24             	add    esp,0x24
  4fe480:	53                   	push   ebx
  4fe481:	ff 15 e0 c4 58 00    	call   DWORD PTR ds:0x58c4e0
  4fe487:	83 c4 04             	add    esp,0x4
  4fe48a:	85 c0                	test   eax,eax
  4fe48c:	0f 85 c4 01 00 00    	jne    0x4fe656
  4fe492:	68 00 04 00 00       	push   0x400
  4fe497:	8d 84 24 54 01 00 00 	lea    eax,[esp+0x154]
  4fe49e:	6a 00                	push   0x0
  4fe4a0:	50                   	push   eax
  4fe4a1:	e8 ba c9 08 00       	call   0x58ae60
  4fe4a6:	83 c4 0c             	add    esp,0xc
  4fe4a9:	8d 84 24 50 09 00 00 	lea    eax,[esp+0x950]
  4fe4b0:	68 00 04 00 00       	push   0x400
  4fe4b5:	6a 00                	push   0x0
  4fe4b7:	50                   	push   eax
  4fe4b8:	e8 a3 c9 08 00       	call   0x58ae60
  4fe4bd:	83 c4 0c             	add    esp,0xc
  4fe4c0:	8d 84 24 50 05 00 00 	lea    eax,[esp+0x550]
  4fe4c7:	68 00 04 00 00       	push   0x400
  4fe4cc:	6a 00                	push   0x0
  4fe4ce:	50                   	push   eax
  4fe4cf:	e8 8c c9 08 00       	call   0x58ae60
  4fe4d4:	83 c4 0c             	add    esp,0xc
  4fe4d7:	8d 8c 24 50 01 00 00 	lea    ecx,[esp+0x150]
  4fe4de:	ba fc 03 00 00       	mov    edx,0x3fc
  4fe4e3:	53                   	push   ebx
  4fe4e4:	e8 97 5d fd ff       	call   0x4d4280
  4fe4e9:	8d 8c 24 54 01 00 00 	lea    ecx,[esp+0x154]
  4fe4f0:	83 c4 04             	add    esp,0x4
  4fe4f3:	8d 51 01             	lea    edx,[ecx+0x1]
  4fe4f6:	8a 01                	mov    al,BYTE PTR [ecx]
  4fe4f8:	41                   	inc    ecx
  4fe4f9:	84 c0                	test   al,al
  4fe4fb:	75 f9                	jne    0x4fe4f6
  4fe4fd:	2b ca                	sub    ecx,edx
  4fe4ff:	75 12                	jne    0x4fe513
  4fe501:	53                   	push   ebx
  4fe502:	ff 15 e0 c4 58 00    	call   DWORD PTR ds:0x58c4e0
  4fe508:	83 c4 04             	add    esp,0x4
  4fe50b:	85 c0                	test   eax,eax
  4fe50d:	0f 85 43 01 00 00    	jne    0x4fe656
  4fe513:	8d 84 24 50 01 00 00 	lea    eax,[esp+0x150]
  4fe51a:	6a 7c                	push   0x7c
  4fe51c:	50                   	push   eax
  4fe51d:	ff 15 48 c3 58 00    	call   DWORD PTR ds:0x58c348
  4fe523:	8b f0                	mov    esi,eax
  4fe525:	83 c4 08             	add    esp,0x8
  4fe528:	85 f6                	test   esi,esi
  4fe52a:	74 39                	je     0x4fe565
  4fe52c:	8d 84 24 50 01 00 00 	lea    eax,[esp+0x150]
  4fe533:	8b ce                	mov    ecx,esi
  4fe535:	2b c8                	sub    ecx,eax
  4fe537:	51                   	push   ecx
  4fe538:	50                   	push   eax
  4fe539:	8d 84 24 58 05 00 00 	lea    eax,[esp+0x558]
  4fe540:	50                   	push   eax
  4fe541:	ff 15 f0 c4 58 00    	call   DWORD PTR ds:0x58c4f0
  4fe547:	8d 4e 02             	lea    ecx,[esi+0x2]
  4fe54a:	83 c4 0c             	add    esp,0xc
  4fe54d:	8d 94 24 50 09 00 00 	lea    edx,[esp+0x950]
  4fe554:	2b d1                	sub    edx,ecx
  4fe556:	8a 01                	mov    al,BYTE PTR [ecx]
  4fe558:	8d 49 01             	lea    ecx,[ecx+0x1]
  4fe55b:	88 44 0a ff          	mov    BYTE PTR [edx+ecx*1-0x1],al
  4fe55f:	84 c0                	test   al,al
  4fe561:	75 f3                	jne    0x4fe556
  4fe563:	eb 30                	jmp    0x4fe595
  4fe565:	68 00 04 00 00       	push   0x400
  4fe56a:	8d 84 24 54 05 00 00 	lea    eax,[esp+0x554]
  4fe571:	6a 00                	push   0x0
  4fe573:	50                   	push   eax
  4fe574:	e8 e7 c8 08 00       	call   0x58ae60
  4fe579:	83 c4 0c             	add    esp,0xc
  4fe57c:	33 c9                	xor    ecx,ecx
  4fe57e:	66 90                	xchg   ax,ax
  4fe580:	8a 84 0c 50 01 00 00 	mov    al,BYTE PTR [esp+ecx*1+0x150]
  4fe587:	8d 49 01             	lea    ecx,[ecx+0x1]
  4fe58a:	88 84 0c 4f 09 00 00 	mov    BYTE PTR [esp+ecx*1+0x94f],al
  4fe591:	84 c0                	test   al,al
  4fe593:	75 eb                	jne    0x4fe580
  4fe595:	8b 74 24 14          	mov    esi,DWORD PTR [esp+0x14]
  4fe599:	8d 8c 24 50 05 00 00 	lea    ecx,[esp+0x550]
  4fe5a0:	6b d7 64             	imul   edx,edi,0x64
  4fe5a3:	46                   	inc    esi
  4fe5a4:	8b c1                	mov    eax,ecx
  4fe5a6:	89 74 24 14          	mov    DWORD PTR [esp+0x14],esi
  4fe5aa:	2b d0                	sub    edx,eax
  4fe5ac:	0f 1f 40 00          	nop    DWORD PTR [eax+0x0]
  4fe5b0:	8a 01                	mov    al,BYTE PTR [ecx]
  4fe5b2:	8d 49 01             	lea    ecx,[ecx+0x1]
  4fe5b5:	88 84 0a 8f 61 5a 06 	mov    BYTE PTR [edx+ecx*1+0x65a618f],al
  4fe5bc:	84 c0                	test   al,al
  4fe5be:	75 f0                	jne    0x4fe5b0
  4fe5c0:	8d 8c 24 50 09 00 00 	lea    ecx,[esp+0x950]
  4fe5c7:	8b d7                	mov    edx,edi
  4fe5c9:	c1 e2 0a             	shl    edx,0xa
  4fe5cc:	8b c1                	mov    eax,ecx
  4fe5ce:	2b d0                	sub    edx,eax
  4fe5d0:	8a 01                	mov    al,BYTE PTR [ecx]
  4fe5d2:	8d 49 01             	lea    ecx,[ecx+0x1]
  4fe5d5:	88 84 0a af 9d 5a 06 	mov    BYTE PTR [edx+ecx*1+0x65a9daf],al
  4fe5dc:	84 c0                	test   al,al
  4fe5de:	75 f0                	jne    0x4fe5d0
  4fe5e0:	8d 8c 24 50 09 00 00 	lea    ecx,[esp+0x950]
  4fe5e7:	89 34 bd a0 9a 5a 06 	mov    DWORD PTR [edi*4+0x65a9aa0],esi
  4fe5ee:	8d 51 01             	lea    edx,[ecx+0x1]
  4fe5f1:	8a 01                	mov    al,BYTE PTR [ecx]
  4fe5f3:	41                   	inc    ecx
  4fe5f4:	84 c0                	test   al,al
  4fe5f6:	75 f9                	jne    0x4fe5f1
  4fe5f8:	2b ca                	sub    ecx,edx
  4fe5fa:	8d 04 cd 00 00 00 00 	lea    eax,[ecx*8+0x0]
  4fe601:	3d 0c 03 00 00       	cmp    eax,0x30c
  4fe606:	0f 9d c0             	setge  al
  4fe609:	fe c0                	inc    al
  4fe60b:	88 87 68 9d 5a 06    	mov    BYTE PTR [edi+0x65a9d68],al
  4fe611:	47                   	inc    edi
  4fe612:	83 ff 46             	cmp    edi,0x46
  4fe615:	75 08                	jne    0x4fe61f
  4fe617:	33 ff                	xor    edi,edi
  4fe619:	89 7c 24 18          	mov    DWORD PTR [esp+0x18],edi
  4fe61d:	eb 0b                	jmp    0x4fe62a
  4fe61f:	8d 77 ff             	lea    esi,[edi-0x1]
  4fe622:	89 74 24 18          	mov    DWORD PTR [esp+0x18],esi
  4fe626:	8b 74 24 14          	mov    esi,DWORD PTR [esp+0x14]
  4fe62a:	8b 44 24 10          	mov    eax,DWORD PTR [esp+0x10]
  4fe62e:	85 c0                	test   eax,eax
  4fe630:	74 04                	je     0x4fe636
  4fe632:	3b f0                	cmp    esi,eax
  4fe634:	7d 20                	jge    0x4fe656
  4fe636:	53                   	push   ebx
  4fe637:	ff 15 e0 c4 58 00    	call   DWORD PTR ds:0x58c4e0
  4fe63d:	83 c4 04             	add    esp,0x4
  4fe640:	85 c0                	test   eax,eax
  4fe642:	75 12                	jne    0x4fe656
  4fe644:	53                   	push   ebx
  4fe645:	ff 15 e0 c4 58 00    	call   DWORD PTR ds:0x58c4e0
  4fe64b:	83 c4 04             	add    esp,0x4
  4fe64e:	85 c0                	test   eax,eax
  4fe650:	0f 84 3c fe ff ff    	je     0x4fe492
  4fe656:	53                   	push   ebx
  4fe657:	ff 15 b4 c4 58 00    	call   DWORD PTR ds:0x58c4b4
  4fe65d:	8b 44 24 24          	mov    eax,DWORD PTR [esp+0x24]
  4fe661:	83 c4 04             	add    esp,0x4
  4fe664:	8b 7c 24 28          	mov    edi,DWORD PTR [esp+0x28]
  4fe668:	85 c0                	test   eax,eax
  4fe66a:	8b 5c 24 18          	mov    ebx,DWORD PTR [esp+0x18]
  4fe66e:	8b cb                	mov    ecx,ebx
  4fe670:	0f 44 c6             	cmove  eax,esi
  4fe673:	c7 44 24 3c 1e 00 00 	mov    DWORD PTR [esp+0x3c],0x1e
  4fe67a:	00 
  4fe67b:	4f                   	dec    edi
  4fe67c:	89 44 24 20          	mov    DWORD PTR [esp+0x20],eax
  4fe680:	33 f6                	xor    esi,esi
  4fe682:	33 d2                	xor    edx,edx
  4fe684:	85 ff                	test   edi,edi
  4fe686:	7e 29                	jle    0x4fe6b1
  4fe688:	8d 5e 45             	lea    ebx,[esi+0x45]
  4fe68b:	0f 1f 44 00 00       	nop    DWORD PTR [eax+eax*1+0x0]
  4fe690:	80 b9 68 9d 5a 06 01 	cmp    BYTE PTR [ecx+0x65a9d68],0x1
  4fe697:	75 01                	jne    0x4fe69a
  4fe699:	46                   	inc    esi
  4fe69a:	85 c9                	test   ecx,ecx
  4fe69c:	8d 41 ff             	lea    eax,[ecx-0x1]
  4fe69f:	0f 44 c3             	cmove  eax,ebx
  4fe6a2:	8b c8                	mov    ecx,eax
  4fe6a4:	3b f7                	cmp    esi,edi
  4fe6a6:	7d 05                	jge    0x4fe6ad
  4fe6a8:	42                   	inc    edx
  4fe6a9:	3b d7                	cmp    edx,edi
  4fe6ab:	7c e3                	jl     0x4fe690
  4fe6ad:	8b 5c 24 18          	mov    ebx,DWORD PTR [esp+0x18]
  4fe6b1:	8b fb                	mov    edi,ebx
  4fe6b3:	2b fe                	sub    edi,esi
  4fe6b5:	89 7c 24 24          	mov    DWORD PTR [esp+0x24],edi
  4fe6b9:	79 29                	jns    0x4fe6e4
  4fe6bb:	b9 b0 b1 5b 06       	mov    ecx,0x65bb1b0
  4fe6c0:	8d 51 01             	lea    edx,[ecx+0x1]
  4fe6c3:	8a 01                	mov    al,BYTE PTR [ecx]
  4fe6c5:	41                   	inc    ecx
  4fe6c6:	84 c0                	test   al,al
  4fe6c8:	75 f9                	jne    0x4fe6c3
  4fe6ca:	2b ca                	sub    ecx,edx
  4fe6cc:	75 04                	jne    0x4fe6d2
  4fe6ce:	33 ff                	xor    edi,edi
  4fe6d0:	eb 0e                	jmp    0x4fe6e0
  4fe6d2:	8b c7                	mov    eax,edi
  4fe6d4:	bf 46 00 00 00       	mov    edi,0x46
  4fe6d9:	99                   	cdq
  4fe6da:	33 c2                	xor    eax,edx
  4fe6dc:	2b c2                	sub    eax,edx
  4fe6de:	2b f8                	sub    edi,eax
  4fe6e0:	89 7c 24 24          	mov    DWORD PTR [esp+0x24],edi
  4fe6e4:	8b 04 bd a0 9a 5a 06 	mov    eax,DWORD PTR [edi*4+0x65a9aa0]
  4fe6eb:	46                   	inc    esi
  4fe6ec:	8b 1c 9d a0 9a 5a 06 	mov    ebx,DWORD PTR [ebx*4+0x65a9aa0]
  4fe6f3:	33 c9                	xor    ecx,ecx
  4fe6f5:	89 44 24 2c          	mov    DWORD PTR [esp+0x2c],eax
  4fe6f9:	89 74 24 44          	mov    DWORD PTR [esp+0x44],esi
  4fe6fd:	89 4c 24 40          	mov    DWORD PTR [esp+0x40],ecx
  4fe701:	85 f6                	test   esi,esi
  4fe703:	0f 8e ee 02 00 00    	jle    0x4fe9f7
  4fe709:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [eax+0x0]
  4fe710:	33 c0                	xor    eax,eax
  4fe712:	8d 34 39             	lea    esi,[ecx+edi*1]
  4fe715:	89 44 24 30          	mov    DWORD PTR [esp+0x30],eax
  4fe719:	89 44 24 34          	mov    DWORD PTR [esp+0x34],eax
  4fe71d:	89 44 24 38          	mov    DWORD PTR [esp+0x38],eax
  4fe721:	83 fe 46             	cmp    esi,0x46
  4fe724:	7c 05                	jl     0x4fe72b
  4fe726:	8d 77 ba             	lea    esi,[edi-0x46]
  4fe729:	03 f1                	add    esi,ecx
  4fe72b:	8b 04 b5 a0 9a 5a 06 	mov    eax,DWORD PTR [esi*4+0x65a9aa0]
  4fe732:	85 c0                	test   eax,eax
  4fe734:	74 05                	je     0x4fe73b
  4fe736:	3b c3                	cmp    eax,ebx
  4fe738:	0f 43 d8             	cmovae ebx,eax
  4fe73b:	6b c6 64             	imul   eax,esi,0x64
  4fe73e:	6a 28                	push   0x28
  4fe740:	8d b8 90 61 5a 06    	lea    edi,[eax+0x65a6190]
  4fe746:	57                   	push   edi
  4fe747:	ff 15 48 c3 58 00    	call   DWORD PTR ds:0x58c348
  4fe74d:	83 c4 08             	add    esp,0x8
  4fe750:	85 c0                	test   eax,eax
  4fe752:	0f 84 06 01 00 00    	je     0x4fe85e
  4fe758:	ba f4 64 59 00       	mov    edx,0x5964f4
  4fe75d:	8b cf                	mov    ecx,edi
  4fe75f:	e8 9c 13 06 00       	call   0x55fb00
  4fe764:	8d 94 24 e8 00 00 00 	lea    edx,[esp+0xe8]
  4fe76b:	2b d0                	sub    edx,eax
  4fe76d:	0f 1f 00             	nop    DWORD PTR [eax]
  4fe770:	8a 08                	mov    cl,BYTE PTR [eax]
  4fe772:	8d 40 01             	lea    eax,[eax+0x1]
  4fe775:	88 4c 02 ff          	mov    BYTE PTR [edx+eax*1-0x1],cl
  4fe779:	84 c9                	test   cl,cl
  4fe77b:	75 f3                	jne    0x4fe770
  4fe77d:	68 00 04 00 00       	push   0x400
  4fe782:	8d 84 24 54 01 00 00 	lea    eax,[esp+0x154]
  4fe789:	6a 00                	push   0x0
  4fe78b:	50                   	push   eax
  4fe78c:	e8 cf c6 08 00       	call   0x58ae60
  4fe791:	83 c4 0c             	add    esp,0xc
  4fe794:	8d 84 24 e8 00 00 00 	lea    eax,[esp+0xe8]
  4fe79b:	6a 02                	push   0x2
  4fe79d:	50                   	push   eax
  4fe79e:	8d 84 24 58 01 00 00 	lea    eax,[esp+0x158]
  4fe7a5:	50                   	push   eax
  4fe7a6:	ff 15 f0 c4 58 00    	call   DWORD PTR ds:0x58c4f0
  4fe7ac:	83 c4 0c             	add    esp,0xc
  4fe7af:	8d 84 24 50 01 00 00 	lea    eax,[esp+0x150]
  4fe7b6:	6a 10                	push   0x10
  4fe7b8:	6a 00                	push   0x0
  4fe7ba:	50                   	push   eax
  4fe7bb:	ff 15 70 c3 58 00    	call   DWORD PTR ds:0x58c370
  4fe7c1:	83 c4 0c             	add    esp,0xc
  4fe7c4:	89 44 24 30          	mov    DWORD PTR [esp+0x30],eax
  4fe7c8:	8d 84 24 50 01 00 00 	lea    eax,[esp+0x150]
  4fe7cf:	68 00 04 00 00       	push   0x400
  4fe7d4:	6a 00                	push   0x0
  4fe7d6:	50                   	push   eax
  4fe7d7:	e8 84 c6 08 00       	call   0x58ae60
  4fe7dc:	83 c4 0c             	add    esp,0xc
  4fe7df:	8d 84 24 ea 00 00 00 	lea    eax,[esp+0xea]
  4fe7e6:	6a 02                	push   0x2
  4fe7e8:	50                   	push   eax
  4fe7e9:	8d 84 24 58 01 00 00 	lea    eax,[esp+0x158]
  4fe7f0:	50                   	push   eax
  4fe7f1:	ff 15 f0 c4 58 00    	call   DWORD PTR ds:0x58c4f0
  4fe7f7:	83 c4 0c             	add    esp,0xc
  4fe7fa:	8d 84 24 50 01 00 00 	lea    eax,[esp+0x150]
  4fe801:	6a 10                	push   0x10
  4fe803:	6a 00                	push   0x0
  4fe805:	50                   	push   eax
  4fe806:	ff 15 70 c3 58 00    	call   DWORD PTR ds:0x58c370
  4fe80c:	83 c4 0c             	add    esp,0xc
  4fe80f:	89 44 24 34          	mov    DWORD PTR [esp+0x34],eax
  4fe813:	8d 84 24 50 01 00 00 	lea    eax,[esp+0x150]
  4fe81a:	68 00 04 00 00       	push   0x400
  4fe81f:	6a 00                	push   0x0
  4fe821:	50                   	push   eax
  4fe822:	e8 39 c6 08 00       	call   0x58ae60
  4fe827:	83 c4 0c             	add    esp,0xc
  4fe82a:	8d 84 24 ec 00 00 00 	lea    eax,[esp+0xec]
  4fe831:	6a 02                	push   0x2
  4fe833:	50                   	push   eax
  4fe834:	8d 84 24 58 01 00 00 	lea    eax,[esp+0x158]
  4fe83b:	50                   	push   eax
  4fe83c:	ff 15 f0 c4 58 00    	call   DWORD PTR ds:0x58c4f0
  4fe842:	83 c4 0c             	add    esp,0xc
  4fe845:	8d 84 24 50 01 00 00 	lea    eax,[esp+0x150]
  4fe84c:	6a 10                	push   0x10
  4fe84e:	6a 00                	push   0x0
  4fe850:	50                   	push   eax
  4fe851:	ff 15 70 c3 58 00    	call   DWORD PTR ds:0x58c370
  4fe857:	83 c4 0c             	add    esp,0xc
  4fe85a:	89 44 24 38          	mov    DWORD PTR [esp+0x38],eax
  4fe85e:	c1 e6 0a             	shl    esi,0xa
  4fe861:	b9 01 00 00 00       	mov    ecx,0x1
  4fe866:	81 c6 b0 9d 5a 06    	add    esi,0x65a9db0
  4fe86c:	8b d6                	mov    edx,esi
  4fe86e:	e8 8d 3a 06 00       	call   0x562300
  4fe873:	83 3d a0 28 6d 0a 00 	cmp    DWORD PTR ds:0xa6d28a0,0x0
  4fe87a:	0f 84 dc 00 00 00    	je     0x4fe95c
  4fe880:	6a 64                	push   0x64
  4fe882:	8d 84 24 84 00 00 00 	lea    eax,[esp+0x84]
  4fe889:	6a 00                	push   0x0
  4fe88b:	50                   	push   eax
  4fe88c:	e8 cf c5 08 00       	call   0x58ae60
  4fe891:	83 c4 0c             	add    esp,0xc
  4fe894:	6a 7b                	push   0x7b
  4fe896:	57                   	push   edi
  4fe897:	ff 15 48 c3 58 00    	call   DWORD PTR ds:0x58c348
  4fe89d:	83 c4 08             	add    esp,0x8
  4fe8a0:	85 c0                	test   eax,eax
  4fe8a2:	0f 84 b4 00 00 00    	je     0x4fe95c
  4fe8a8:	ba 18 9f 5a 00       	mov    edx,0x5a9f18
  4fe8ad:	8b cf                	mov    ecx,edi
  4fe8af:	e8 4c 12 06 00       	call   0x55fb00
  4fe8b4:	8d 94 24 80 00 00 00 	lea    edx,[esp+0x80]
  4fe8bb:	2b d0                	sub    edx,eax
  4fe8bd:	0f 1f 00             	nop    DWORD PTR [eax]
  4fe8c0:	8a 08                	mov    cl,BYTE PTR [eax]
  4fe8c2:	8d 40 01             	lea    eax,[eax+0x1]
  4fe8c5:	88 4c 02 ff          	mov    BYTE PTR [edx+eax*1-0x1],cl
  4fe8c9:	84 c9                	test   cl,cl
  4fe8cb:	75 f3                	jne    0x4fe8c0
  4fe8cd:	8b 35 f0 c4 58 00    	mov    esi,DWORD PTR ds:0x58c4f0
  4fe8d3:	8d 84 24 80 00 00 00 	lea    eax,[esp+0x80]
  4fe8da:	6a 04                	push   0x4
  4fe8dc:	50                   	push   eax
  4fe8dd:	8d 44 24 7c          	lea    eax,[esp+0x7c]
  4fe8e1:	66 c7 84 24 84 00 00 	mov    WORD PTR [esp+0x84],0x0
  4fe8e8:	00 00 00 
  4fe8eb:	0f 57 c0             	xorps  xmm0,xmm0
  4fe8ee:	50                   	push   eax
  4fe8ef:	66 0f d6 84 24 80 00 	movq   QWORD PTR [esp+0x80],xmm0
  4fe8f6:	00 00 
  4fe8f8:	ff d6                	call   esi
  4fe8fa:	83 c4 0c             	add    esp,0xc
  4fe8fd:	66 c7 44 24 70 00 00 	mov    WORD PTR [esp+0x70],0x0
  4fe904:	8d 84 24 84 00 00 00 	lea    eax,[esp+0x84]
  4fe90b:	0f 57 c0             	xorps  xmm0,xmm0
  4fe90e:	66 0f d6 44 24 68    	movq   QWORD PTR [esp+0x68],xmm0
  4fe914:	6a 04                	push   0x4
  4fe916:	50                   	push   eax
  4fe917:	8d 44 24 70          	lea    eax,[esp+0x70]
  4fe91b:	50                   	push   eax
  4fe91c:	ff d6                	call   esi
  4fe91e:	83 c4 0c             	add    esp,0xc
  4fe921:	8d 4c 24 68          	lea    ecx,[esp+0x68]
  4fe925:	e8 b6 21 fd ff       	call   0x4d0ae0
  4fe92a:	50                   	push   eax
  4fe92b:	51                   	push   ecx
  4fe92c:	8d 4c 24 7c          	lea    ecx,[esp+0x7c]
  4fe930:	e8 ab 21 fd ff       	call   0x4d0ae0
  4fe935:	83 c4 04             	add    esp,0x4
  4fe938:	50                   	push   eax
  4fe939:	8d 84 24 88 00 00 00 	lea    eax,[esp+0x88]
  4fe940:	68 30 ac 5a 00       	push   0x5aac30
  4fe945:	50                   	push   eax
  4fe946:	e8 85 27 f0 ff       	call   0x4010d0
  4fe94b:	83 c4 10             	add    esp,0x10
  4fe94e:	8d 94 24 80 00 00 00 	lea    edx,[esp+0x80]
  4fe955:	33 c9                	xor    ecx,ecx
  4fe957:	e8 a4 39 06 00       	call   0x562300
  4fe95c:	8b 44 24 30          	mov    eax,DWORD PTR [esp+0x30]
  4fe960:	be ff 00 00 00       	mov    esi,0xff
  4fe965:	8b 4c 24 34          	mov    ecx,DWORD PTR [esp+0x34]
  4fe969:	3d ff 00 00 00       	cmp    eax,0xff
  4fe96e:	8b 54 24 38          	mov    edx,DWORD PTR [esp+0x38]
  4fe972:	0f 4f c6             	cmovg  eax,esi
  4fe975:	3b ce                	cmp    ecx,esi
  4fe977:	0f 4f ce             	cmovg  ecx,esi
  4fe97a:	3b d6                	cmp    edx,esi
  4fe97c:	0f 4f d6             	cmovg  edx,esi
  4fe97f:	52                   	push   edx
  4fe980:	51                   	push   ecx
  4fe981:	50                   	push   eax
  4fe982:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4fe987:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fe98a:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  4fe990:	66 0f 6e 05 bc 6a 5e 	movd   xmm0,DWORD PTR ds:0x5e6abc
  4fe997:	00 
  4fe998:	8b 74 24 4c          	mov    esi,DWORD PTR [esp+0x4c]
  4fe99c:	8b d6                	mov    edx,esi
  4fe99e:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4fe9a1:	6a 00                	push   0x0
  4fe9a3:	50                   	push   eax
  4fe9a4:	f3 0f 59 05 98 d4 5d 	mulss  xmm0,DWORD PTR ds:0x5dd498
  4fe9ab:	00 
  4fe9ac:	f3 0f 2c c8          	cvttss2si ecx,xmm0
  4fe9b0:	51                   	push   ecx
  4fe9b1:	68 0c 03 00 00       	push   0x30c
  4fe9b6:	b9 0a 00 00 00       	mov    ecx,0xa
  4fe9bb:	e8 80 01 01 00       	call   0x50eb40
  4fe9c0:	66 0f 6e 05 bc 6a 5e 	movd   xmm0,DWORD PTR ds:0x5e6abc
  4fe9c7:	00 
  4fe9c8:	83 c4 20             	add    esp,0x20
  4fe9cb:	8b 7c 24 24          	mov    edi,DWORD PTR [esp+0x24]
  4fe9cf:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4fe9d2:	f3 0f 2c c8          	cvttss2si ecx,xmm0
  4fe9d6:	03 c8                	add    ecx,eax
  4fe9d8:	03 f1                	add    esi,ecx
  4fe9da:	8b 4c 24 40          	mov    ecx,DWORD PTR [esp+0x40]
  4fe9de:	41                   	inc    ecx
  4fe9df:	89 74 24 3c          	mov    DWORD PTR [esp+0x3c],esi
  4fe9e3:	8b 74 24 44          	mov    esi,DWORD PTR [esp+0x44]
  4fe9e7:	89 4c 24 40          	mov    DWORD PTR [esp+0x40],ecx
  4fe9eb:	3b ce                	cmp    ecx,esi
  4fe9ed:	0f 8c 1d fd ff ff    	jl     0x4fe710
  4fe9f3:	8b 44 24 2c          	mov    eax,DWORD PTR [esp+0x2c]
  4fe9f7:	8b 7c 24 20          	mov    edi,DWORD PTR [esp+0x20]
  4fe9fb:	57                   	push   edi
  4fe9fc:	53                   	push   ebx
  4fe9fd:	50                   	push   eax
  4fe9fe:	8d 84 24 5c 01 00 00 	lea    eax,[esp+0x15c]
  4fea05:	68 40 ac 5a 00       	push   0x5aac40
  4fea0a:	50                   	push   eax
  4fea0b:	e8 c0 26 f0 ff       	call   0x4010d0
  4fea10:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4fea15:	83 c4 14             	add    esp,0x14
  4fea18:	6a 57                	push   0x57
  4fea1a:	6a 57                	push   0x57
  4fea1c:	6a 57                	push   0x57
  4fea1e:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fea21:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  4fea27:	6a 00                	push   0x0
  4fea29:	50                   	push   eax
  4fea2a:	8d 84 24 68 01 00 00 	lea    eax,[esp+0x168]
  4fea31:	ba 44 02 00 00       	mov    edx,0x244
  4fea36:	50                   	push   eax
  4fea37:	b9 2c 01 00 00       	mov    ecx,0x12c
  4fea3c:	e8 5f fb 00 00       	call   0x50e5a0
  4fea41:	83 c4 1c             	add    esp,0x1c
  4fea44:	ba 16 c6 58 00       	mov    edx,0x58c616
  4fea49:	33 c9                	xor    ecx,ecx
  4fea4b:	6a 64                	push   0x64
  4fea4d:	6a 32                	push   0x32
  4fea4f:	68 0c 03 00 00       	push   0x30c
  4fea54:	68 26 02 00 00       	push   0x226
  4fea59:	6a 00                	push   0x0
  4fea5b:	e8 30 0d fd ff       	call   0x4cf790
  4fea60:	83 c4 14             	add    esp,0x14
  4fea63:	c7 05 9c 4a 35 06 00 	mov    DWORD PTR ds:0x6354a9c,0x0
  4fea6a:	00 00 00 
  4fea6d:	8d 84 24 50 01 00 00 	lea    eax,[esp+0x150]
  4fea74:	c7 05 a0 4a 35 06 01 	mov    DWORD PTR ds:0x6354aa0,0x1
  4fea7b:	00 00 00 
  4fea7e:	6a 18                	push   0x18
  4fea80:	68 dc d6 58 00       	push   0x58d6dc
  4fea85:	50                   	push   eax
  4fea86:	e8 45 26 f0 ff       	call   0x4010d0
  4fea8b:	83 c4 0c             	add    esp,0xc
  4fea8e:	8d 84 24 50 01 00 00 	lea    eax,[esp+0x150]
  4fea95:	ba 0a 00 00 00       	mov    edx,0xa
  4fea9a:	b9 30 04 00 00       	mov    ecx,0x430
  4fea9f:	50                   	push   eax
  4feaa0:	68 3f 02 00 00       	push   0x23f
  4feaa5:	e8 46 10 fd ff       	call   0x4cfaf0
  4feaaa:	6a 19                	push   0x19
  4feaac:	8d 84 24 5c 01 00 00 	lea    eax,[esp+0x15c]
  4feab3:	68 dc d6 58 00       	push   0x58d6dc
  4feab8:	50                   	push   eax
  4feab9:	e8 12 26 f0 ff       	call   0x4010d0
  4feabe:	83 c4 14             	add    esp,0x14
  4feac1:	8d 84 24 50 01 00 00 	lea    eax,[esp+0x150]
  4feac8:	ba 1e 00 00 00       	mov    edx,0x1e
  4feacd:	b9 38 04 00 00       	mov    ecx,0x438
  4fead2:	50                   	push   eax
  4fead3:	68 3f 02 00 00       	push   0x23f
  4fead8:	e8 13 10 fd ff       	call   0x4cfaf0
  4feadd:	68 50 ac 5a 00       	push   0x5aac50
  4feae2:	68 3f 02 00 00       	push   0x23f
  4feae7:	ba 37 00 00 00       	mov    edx,0x37
  4feaec:	b9 31 04 00 00       	mov    ecx,0x431
  4feaf1:	e8 fa 0f fd ff       	call   0x4cfaf0
  4feaf6:	68 58 ac 5a 00       	push   0x5aac58
  4feafb:	68 3f 02 00 00       	push   0x23f
  4feb00:	ba 64 00 00 00       	mov    edx,0x64
  4feb05:	b9 39 04 00 00       	mov    ecx,0x439
  4feb0a:	e8 e1 0f fd ff       	call   0x4cfaf0
  4feb0f:	8d 84 24 68 01 00 00 	lea    eax,[esp+0x168]
  4feb16:	68 c8 50 59 00       	push   0x5950c8
  4feb1b:	50                   	push   eax
  4feb1c:	e8 af 25 f0 ff       	call   0x4010d0
  4feb21:	8d 84 24 70 01 00 00 	lea    eax,[esp+0x170]
  4feb28:	ba a0 00 00 00       	mov    edx,0xa0
  4feb2d:	50                   	push   eax
  4feb2e:	68 3f 02 00 00       	push   0x23f
  4feb33:	b9 1b 00 00 00       	mov    ecx,0x1b
  4feb38:	e8 b3 0f fd ff       	call   0x4cfaf0
  4feb3d:	68 60 ac 5a 00       	push   0x5aac60
  4feb42:	8d 84 24 7c 01 00 00 	lea    eax,[esp+0x17c]
  4feb49:	50                   	push   eax
  4feb4a:	e8 81 25 f0 ff       	call   0x4010d0
  4feb4f:	8d 84 24 80 01 00 00 	lea    eax,[esp+0x180]
  4feb56:	ba 26 02 00 00       	mov    edx,0x226
  4feb5b:	50                   	push   eax
  4feb5c:	68 3f 02 00 00       	push   0x23f
  4feb61:	b9 0d 00 00 00       	mov    ecx,0xd
  4feb66:	e8 85 0f fd ff       	call   0x4cfaf0
  4feb6b:	8b 44 24 54          	mov    eax,DWORD PTR [esp+0x54]
  4feb6f:	83 c4 38             	add    esp,0x38
  4feb72:	a3 b0 4a 35 06       	mov    ds:0x6354ab0,eax
  4feb77:	e8 a4 25 fd ff       	call   0x4d1120
  4feb7c:	83 f8 64             	cmp    eax,0x64
  4feb7f:	7c 0f                	jl     0x4feb90
  4feb81:	8b 3d b0 4a 35 06    	mov    edi,DWORD PTR ds:0x6354ab0
  4feb87:	89 7c 24 1c          	mov    DWORD PTR [esp+0x1c],edi
  4feb8b:	e9 90 f7 ff ff       	jmp    0x4fe320
  4feb90:	85 c0                	test   eax,eax
  4feb92:	79 0f                	jns    0x4feba3
  4feb94:	8b 3d b0 4a 35 06    	mov    edi,DWORD PTR ds:0x6354ab0
  4feb9a:	89 7c 24 1c          	mov    DWORD PTR [esp+0x1c],edi
  4feb9e:	e9 7d f7 ff ff       	jmp    0x4fe320
  4feba3:	8b 0d b0 4a 35 06    	mov    ecx,DWORD PTR ds:0x6354ab0
  4feba9:	69 c0 e8 00 00 00    	imul   eax,eax,0xe8
  4febaf:	89 4c 24 1c          	mov    DWORD PTR [esp+0x1c],ecx
  4febb3:	8b 80 d8 ef 34 06    	mov    eax,DWORD PTR [eax+0x634efd8]
  4febb9:	83 f8 1b             	cmp    eax,0x1b
  4febbc:	0f 84 18 02 00 00    	je     0x4fedda
  4febc2:	83 f8 0d             	cmp    eax,0xd
  4febc5:	0f 85 88 01 00 00    	jne    0x4fed53
  4febcb:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4febd0:	8b 1d f8 c1 58 00    	mov    ebx,DWORD PTR ds:0x58c1f8
  4febd6:	68 99 00 00 00       	push   0x99
  4febdb:	68 c5 00 00 00       	push   0xc5
  4febe0:	68 e2 00 00 00       	push   0xe2
  4febe5:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4febe8:	ff d3                	call   ebx
  4febea:	0f 28 05 10 d9 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5dd910
  4febf1:	50                   	push   eax
  4febf2:	8d 44 24 6c          	lea    eax,[esp+0x6c]
  4febf6:	50                   	push   eax
  4febf7:	ff 35 10 bb 5b 06    	push   DWORD PTR ds:0x65bbb10
  4febfd:	0f 11 44 24 74       	movups XMMWORD PTR [esp+0x74],xmm0
  4fec02:	ff 15 e8 c1 58 00    	call   DWORD PTR ds:0x58c1e8
  4fec08:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4fec0d:	83 c4 1c             	add    esp,0x1c
  4fec10:	6a 54                	push   0x54
  4fec12:	68 fc 00 00 00       	push   0xfc
  4fec17:	68 fc 00 00 00       	push   0xfc
  4fec1c:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fec1f:	ff d3                	call   ebx
  4fec21:	83 c4 0c             	add    esp,0xc
  4fec24:	ba 42 02 00 00       	mov    edx,0x242
  4fec29:	b9 0a 00 00 00       	mov    ecx,0xa
  4fec2e:	6a 0f                	push   0xf
  4fec30:	68 0c 03 00 00       	push   0x30c
  4fec35:	e8 46 28 01 00       	call   0x511480
  4fec3a:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4fec3f:	83 c4 0c             	add    esp,0xc
  4fec42:	68 de 00 00 00       	push   0xde
  4fec47:	68 c4 00 00 00       	push   0xc4
  4fec4c:	68 b0 00 00 00       	push   0xb0
  4fec51:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fec54:	ff d3                	call   ebx
  4fec56:	6a 01                	push   0x1
  4fec58:	50                   	push   eax
  4fec59:	68 16 c6 58 00       	push   0x58c616
  4fec5e:	ba 46 02 00 00       	mov    edx,0x246
  4fec63:	b9 0f 00 00 00       	mov    ecx,0xf
  4fec68:	e8 33 f9 00 00       	call   0x50e5a0
  4fec6d:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4fec72:	83 c4 1c             	add    esp,0x1c
  4fec75:	6a 00                	push   0x0
  4fec77:	6a 57                	push   0x57
  4fec79:	6a 57                	push   0x57
  4fec7b:	6a 57                	push   0x57
  4fec7d:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fec80:	ff d3                	call   ebx
  4fec82:	83 c4 10             	add    esp,0x10
  4fec85:	ba 38 02 00 00       	mov    edx,0x238
  4fec8a:	b9 0a 00 00 00       	mov    ecx,0xa
  4fec8f:	50                   	push   eax
  4fec90:	68 7c ac 5a 00       	push   0x5aac7c
  4fec95:	e8 06 f9 00 00       	call   0x50e5a0
  4fec9a:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4fec9f:	83 c4 0c             	add    esp,0xc
  4feca2:	c7 05 b4 1c 5c 0a 0f 	mov    DWORD PTR ds:0xa5c1cb4,0xf
  4feca9:	00 00 00 
  4fecac:	c7 05 3c bb 5b 06 46 	mov    DWORD PTR ds:0x65bbb3c,0x246
  4fecb3:	02 00 00 
  4fecb6:	6a 54                	push   0x54
  4fecb8:	68 fc 00 00 00       	push   0xfc
  4fecbd:	68 fc 00 00 00       	push   0xfc
  4fecc2:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fecc5:	ff d3                	call   ebx
  4fecc7:	83 c4 10             	add    esp,0x10
  4fecca:	ba 5f 00 00 00       	mov    edx,0x5f
  4feccf:	8b c8                	mov    ecx,eax
  4fecd1:	e8 da 08 01 00       	call   0x50f5b0
  4fecd6:	8d 94 24 50 01 00 00 	lea    edx,[esp+0x150]
  4fecdd:	2b d0                	sub    edx,eax
  4fecdf:	90                   	nop
  4fece0:	8a 08                	mov    cl,BYTE PTR [eax]
  4fece2:	8d 40 01             	lea    eax,[eax+0x1]
  4fece5:	88 4c 02 ff          	mov    BYTE PTR [edx+eax*1-0x1],cl
  4fece9:	84 c9                	test   cl,cl
  4feceb:	75 f3                	jne    0x4fece0
  4feced:	8d 8c 24 50 01 00 00 	lea    ecx,[esp+0x150]
  4fecf4:	8d 51 01             	lea    edx,[ecx+0x1]
  4fecf7:	8a 01                	mov    al,BYTE PTR [ecx]
  4fecf9:	41                   	inc    ecx
  4fecfa:	84 c0                	test   al,al
  4fecfc:	75 f9                	jne    0x4fecf7
  4fecfe:	2b ca                	sub    ecx,edx
  4fed00:	83 f9 03             	cmp    ecx,0x3
  4fed03:	0f 86 17 f6 ff ff    	jbe    0x4fe320
  4fed09:	8d 84 24 50 01 00 00 	lea    eax,[esp+0x150]
  4fed10:	50                   	push   eax
  4fed11:	8d 84 24 54 05 00 00 	lea    eax,[esp+0x554]
  4fed18:	68 bc ac 5a 00       	push   0x5aacbc
  4fed1d:	50                   	push   eax
  4fed1e:	e8 ad 23 f0 ff       	call   0x4010d0
  4fed23:	83 c4 0c             	add    esp,0xc
  4fed26:	8d 84 24 50 05 00 00 	lea    eax,[esp+0x550]
  4fed2d:	32 d2                	xor    dl,dl
  4fed2f:	b1 60                	mov    cl,0x60
  4fed31:	50                   	push   eax
  4fed32:	68 54 8e 5a 00       	push   0x5a8e54
  4fed37:	6a 60                	push   0x60
  4fed39:	e8 42 75 ff ff       	call   0x4f6280
  4fed3e:	83 c4 0c             	add    esp,0xc
  4fed41:	c7 44 24 10 00 00 00 	mov    DWORD PTR [esp+0x10],0x0
  4fed48:	00 
  4fed49:	47                   	inc    edi
  4fed4a:	89 7c 24 20          	mov    DWORD PTR [esp+0x20],edi
  4fed4e:	e9 cd f5 ff ff       	jmp    0x4fe320
  4fed53:	3d 30 04 00 00       	cmp    eax,0x430
  4fed58:	75 16                	jne    0x4fed70
  4fed5a:	39 74 24 14          	cmp    DWORD PTR [esp+0x14],esi
  4fed5e:	0f 8e bc f5 ff ff    	jle    0x4fe320
  4fed64:	8d 7b ff             	lea    edi,[ebx-0x1]
  4fed67:	89 7c 24 10          	mov    DWORD PTR [esp+0x10],edi
  4fed6b:	e9 b0 f5 ff ff       	jmp    0x4fe320
  4fed70:	3d 38 04 00 00       	cmp    eax,0x438
  4fed75:	75 12                	jne    0x4fed89
  4fed77:	3b df                	cmp    ebx,edi
  4fed79:	0f 8d a1 f5 ff ff    	jge    0x4fe320
  4fed7f:	43                   	inc    ebx
  4fed80:	89 5c 24 10          	mov    DWORD PTR [esp+0x10],ebx
  4fed84:	e9 97 f5 ff ff       	jmp    0x4fe320
  4fed89:	3d 31 04 00 00       	cmp    eax,0x431
  4fed8e:	75 27                	jne    0x4fedb7
  4fed90:	39 74 24 14          	cmp    DWORD PTR [esp+0x14],esi
  4fed94:	0f 8e 86 f5 ff ff    	jle    0x4fe320
  4fed9a:	8b 44 24 28          	mov    eax,DWORD PTR [esp+0x28]
  4fed9e:	8b fb                	mov    edi,ebx
  4feda0:	2b f8                	sub    edi,eax
  4feda2:	89 7c 24 10          	mov    DWORD PTR [esp+0x10],edi
  4feda6:	3b f8                	cmp    edi,eax
  4feda8:	0f 8d 72 f5 ff ff    	jge    0x4fe320
  4fedae:	89 44 24 10          	mov    DWORD PTR [esp+0x10],eax
  4fedb2:	e9 69 f5 ff ff       	jmp    0x4fe320
  4fedb7:	3d 39 04 00 00       	cmp    eax,0x439
  4fedbc:	0f 85 5e f5 ff ff    	jne    0x4fe320
  4fedc2:	3b df                	cmp    ebx,edi
  4fedc4:	0f 8d 56 f5 ff ff    	jge    0x4fe320
  4fedca:	8b 44 24 28          	mov    eax,DWORD PTR [esp+0x28]
  4fedce:	48                   	dec    eax
  4fedcf:	03 d8                	add    ebx,eax
  4fedd1:	89 5c 24 10          	mov    DWORD PTR [esp+0x10],ebx
  4fedd5:	e9 46 f5 ff ff       	jmp    0x4fe320
  4fedda:	e8 41 e6 00 00       	call   0x50d420
  4feddf:	b9 7c d5 59 00       	mov    ecx,0x59d57c
  4fede4:	c7 05 d8 bc 5b 06 01 	mov    DWORD PTR ds:0x65bbcd8,0x1
  4fedeb:	00 00 00 
  4fedee:	e8 6d c2 00 00       	call   0x50b060
  4fedf3:	33 d2                	xor    edx,edx
  4fedf5:	b9 2c 52 78 0a       	mov    ecx,0xa78522c
  4fedfa:	66 0f 1f 44 00 00    	nop    WORD PTR [eax+eax*1+0x0]
  4fee00:	8a 82 70 ef 80 0a    	mov    al,BYTE PTR [edx+0xa80ef70]
  4fee06:	8d 52 01             	lea    edx,[edx+0x1]
  4fee09:	88 01                	mov    BYTE PTR [ecx],al
  4fee0b:	81 c1 48 0c 00 00    	add    ecx,0xc48
  4fee11:	81 f9 2c 76 7e 0a    	cmp    ecx,0xa7e762c
  4fee17:	7c e7                	jl     0x4fee00
  4fee19:	5f                   	pop    edi
  4fee1a:	5e                   	pop    esi
  4fee1b:	5b                   	pop    ebx
  4fee1c:	8b 8c 24 48 0d 00 00 	mov    ecx,DWORD PTR [esp+0xd48]
  4fee23:	33 cc                	xor    ecx,esp
  4fee25:	e8 84 b2 08 00       	call   0x58a0ae
  4fee2a:	8b e5                	mov    esp,ebp
  4fee2c:	5d                   	pop    ebp
  4fee2d:	c3                   	ret
  4fee2e:	b9 00 ac 5a 00       	mov    ecx,0x5aac00
  4fee33:	e8 d8 76 ff ff       	call   0x4f6510
  4fee38:	8b 8c 24 54 0d 00 00 	mov    ecx,DWORD PTR [esp+0xd54]
  4fee3f:	5f                   	pop    edi
  4fee40:	5e                   	pop    esi
  4fee41:	5b                   	pop    ebx
  4fee42:	33 cc                	xor    ecx,esp
  4fee44:	e8 65 b2 08 00       	call   0x58a0ae
  4fee49:	8b e5                	mov    esp,ebp
  4fee4b:	5d                   	pop    ebp
  4fee4c:	c3                   	ret

/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

004d4280 <.text+0xd3280>:
  4d4280:	55                   	push   ebp
  4d4281:	8b ec                	mov    ebp,esp
  4d4283:	51                   	push   ecx
  4d4284:	53                   	push   ebx
  4d4285:	8b 1d 64 c3 58 00    	mov    ebx,DWORD PTR ds:0x58c364
  4d428b:	8b c2                	mov    eax,edx
  4d428d:	56                   	push   esi
  4d428e:	57                   	push   edi
  4d428f:	8b 3d 50 c3 58 00    	mov    edi,DWORD PTR ds:0x58c350
  4d4295:	8b f1                	mov    esi,ecx
  4d4297:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  4d429a:	66 0f 1f 44 00 00    	nop    WORD PTR [eax+eax*1+0x0]
  4d42a0:	ff 75 08             	push   DWORD PTR [ebp+0x8]
  4d42a3:	50                   	push   eax
  4d42a4:	56                   	push   esi
  4d42a5:	ff 15 c8 c4 58 00    	call   DWORD PTR ds:0x58c4c8
  4d42ab:	83 c4 0c             	add    esp,0xc
  4d42ae:	85 c0                	test   eax,eax
  4d42b0:	74 4b                	je     0x4d42fd
  4d42b2:	6a 0d                	push   0xd
  4d42b4:	56                   	push   esi
  4d42b5:	ff d3                	call   ebx
  4d42b7:	83 c4 08             	add    esp,0x8
  4d42ba:	85 c0                	test   eax,eax
  4d42bc:	74 03                	je     0x4d42c1
  4d42be:	c6 00 00             	mov    BYTE PTR [eax],0x0
  4d42c1:	6a 0a                	push   0xa
  4d42c3:	56                   	push   esi
  4d42c4:	ff d3                	call   ebx
  4d42c6:	83 c4 08             	add    esp,0x8
  4d42c9:	85 c0                	test   eax,eax
  4d42cb:	74 03                	je     0x4d42d0
  4d42cd:	c6 00 00             	mov    BYTE PTR [eax],0x0
  4d42d0:	68 e4 64 59 00       	push   0x5964e4
  4d42d5:	56                   	push   esi
  4d42d6:	ff d7                	call   edi
  4d42d8:	83 c4 08             	add    esp,0x8
  4d42db:	3b c6                	cmp    eax,esi
  4d42dd:	8b 45 fc             	mov    eax,DWORD PTR [ebp-0x4]
  4d42e0:	74 be                	je     0x4d42a0
  4d42e2:	68 ac 50 5a 00       	push   0x5a50ac
  4d42e7:	56                   	push   esi
  4d42e8:	ff d7                	call   edi
  4d42ea:	83 c4 08             	add    esp,0x8
  4d42ed:	3b c6                	cmp    eax,esi
  4d42ef:	8b 45 fc             	mov    eax,DWORD PTR [ebp-0x4]
  4d42f2:	74 ac                	je     0x4d42a0
  4d42f4:	5f                   	pop    edi
  4d42f5:	8b c6                	mov    eax,esi
  4d42f7:	5e                   	pop    esi
  4d42f8:	5b                   	pop    ebx
  4d42f9:	8b e5                	mov    esp,ebp
  4d42fb:	5d                   	pop    ebp
  4d42fc:	c3                   	ret
  4d42fd:	5f                   	pop    edi
  4d42fe:	5e                   	pop    esi
  4d42ff:	33 c0                	xor    eax,eax
  4d4301:	5b                   	pop    ebx
  4d4302:	8b e5                	mov    esp,ebp
  4d4304:	5d                   	pop    ebp
  4d4305:	c3                   	ret
