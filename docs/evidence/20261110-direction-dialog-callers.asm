  404689:	cc                   	int3
  40468a:	cc                   	int3
  40468b:	cc                   	int3
  40468c:	cc                   	int3
  40468d:	cc                   	int3
  40468e:	cc                   	int3
  40468f:	cc                   	int3
  404690:	56                   	push   esi
  404691:	8b f1                	mov    esi,ecx
  404693:	ba a0 cc 58 00       	mov    edx,0x58cca0
  404698:	b1 02                	mov    cl,0x2
  40469a:	e8 81 31 0f 00       	call   0x4f7820
  40469f:	84 c0                	test   al,al
  4046a1:	74 58                	je     0x4046fb

  4058bc:	8b e5                	mov    esp,ebp
  4058be:	5d                   	pop    ebp
  4058bf:	c3                   	ret
  4058c0:	81 fb 8c 01 00 00    	cmp    ebx,0x18c
  4058c6:	0f 8c f6 00 00 00    	jl     0x4059c2
  4058cc:	81 fb 8d 01 00 00    	cmp    ebx,0x18d
  4058d2:	0f 8e b7 00 00 00    	jle    0x40598f
  4058d8:	81 fb 90 01 00 00    	cmp    ebx,0x190
  4058de:	0f 85 de 00 00 00    	jne    0x4059c2
  4058e4:	ba 4c d1 58 00       	mov    edx,0x58d14c
  4058e9:	b1 02                	mov    cl,0x2
  4058eb:	e8 30 1f 0f 00       	call   0x4f7820
  4058f0:	84 c0                	test   al,al
  4058f2:	0f 84 da 04 00 00    	je     0x405dd2

  40597e:	5f                   	pop    edi
  40597f:	5e                   	pop    esi
  405980:	5b                   	pop    ebx
  405981:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  405984:	33 cd                	xor    ecx,ebp
  405986:	e8 23 47 18 00       	call   0x58a0ae
  40598b:	8b e5                	mov    esp,ebp
  40598d:	5d                   	pop    ebp
  40598e:	c3                   	ret
  40598f:	ba c4 d0 58 00       	mov    edx,0x58d0c4
  405994:	b1 02                	mov    cl,0x2
  405996:	e8 85 1e 0f 00       	call   0x4f7820
  40599b:	84 c0                	test   al,al
  40599d:	0f 84 2f 04 00 00    	je     0x405dd2

  406320:	55                   	push   ebp
  406321:	8b ec                	mov    ebp,esp
  406323:	81 ec 74 04 00 00    	sub    esp,0x474
  406329:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  40632e:	33 c5                	xor    eax,ebp
  406330:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  406333:	53                   	push   ebx
  406334:	56                   	push   esi
  406335:	57                   	push   edi
  406336:	ba 34 d4 58 00       	mov    edx,0x58d434
  40633b:	b1 02                	mov    cl,0x2
  40633d:	e8 de 14 0f 00       	call   0x4f7820
  406342:	84 c0                	test   al,al
  406344:	0f 84 71 01 00 00    	je     0x4064bb

  43167f:	77 1c                	ja     0x43169d
  431681:	ff 24 85 24 20 43 00 	jmp    DWORD PTR [eax*4+0x432024]
  431688:	be 1e 00 00 00       	mov    esi,0x1e
  43168d:	eb 13                	jmp    0x4316a2
  43168f:	be 14 00 00 00       	mov    esi,0x14
  431694:	eb 0c                	jmp    0x4316a2
  431696:	be 0a 00 00 00       	mov    esi,0xa
  43169b:	eb 05                	jmp    0x4316a2
  43169d:	be 0f 00 00 00       	mov    esi,0xf
  4316a2:	ba ec 2d 59 00       	mov    edx,0x592dec
  4316a7:	b1 02                	mov    cl,0x2
  4316a9:	e8 72 61 0c 00       	call   0x4f7820
  4316ae:	84 c0                	test   al,al
  4316b0:	0f 84 5b 09 00 00    	je     0x432011

  43b53a:	5f                   	pop    edi
  43b53b:	5e                   	pop    esi
  43b53c:	5b                   	pop    ebx
  43b53d:	8b 8c 24 90 05 00 00 	mov    ecx,DWORD PTR [esp+0x590]
  43b544:	33 cc                	xor    ecx,esp
  43b546:	e8 63 eb 14 00       	call   0x58a0ae
  43b54b:	8b e5                	mov    esp,ebp
  43b54d:	5d                   	pop    ebp
  43b54e:	c3                   	ret
  43b54f:	ba a8 43 59 00       	mov    edx,0x5943a8
  43b554:	b1 12                	mov    cl,0x12
  43b556:	e8 c5 c2 0b 00       	call   0x4f7820
  43b55b:	84 c0                	test   al,al
  43b55d:	75 1f                	jne    0x43b57e

  44603e:	33 ff                	xor    edi,edi
  446040:	89 8d 70 fb ff ff    	mov    DWORD PTR [ebp-0x490],ecx
  446046:	88 bd 7c fb ff ff    	mov    BYTE PTR [ebp-0x484],bh
  44604c:	c7 85 78 fb ff ff 00 	mov    DWORD PTR [ebp-0x488],0x0
  446053:	00 00 00 
  446056:	c7 85 80 fb ff ff 00 	mov    DWORD PTR [ebp-0x480],0x0
  44605d:	00 00 00 
  446060:	85 d2                	test   edx,edx
  446062:	75 3a                	jne    0x44609e
  446064:	ba f0 6f 59 00       	mov    edx,0x596ff0
  446069:	b1 02                	mov    cl,0x2
  44606b:	e8 b0 17 0b 00       	call   0x4f7820
  446070:	88 85 8b fb ff ff    	mov    BYTE PTR [ebp-0x475],al
  446076:	88 85 68 fb ff ff    	mov    BYTE PTR [ebp-0x498],al

  44cf7d:	cc                   	int3
  44cf7e:	cc                   	int3
  44cf7f:	cc                   	int3
  44cf80:	53                   	push   ebx
  44cf81:	56                   	push   esi
  44cf82:	8b f1                	mov    esi,ecx
  44cf84:	b9 10 87 59 00       	mov    ecx,0x598710
  44cf89:	57                   	push   edi
  44cf8a:	e8 81 95 0a 00       	call   0x4f6510
  44cf8f:	ba 68 87 59 00       	mov    edx,0x598768
  44cf94:	b1 02                	mov    cl,0x2
  44cf96:	e8 85 a8 0a 00       	call   0x4f7820
  44cf9b:	84 c0                	test   al,al
  44cf9d:	74 63                	je     0x44d002

  44d18e:	e8 3d 28 05 00       	call   0x49f9d0
  44d193:	85 c0                	test   eax,eax
  44d195:	0f 85 1d 03 00 00    	jne    0x44d4b8
  44d19b:	8b 04 9d d0 ac 72 0a 	mov    eax,DWORD PTR [ebx*4+0xa72acd0]
  44d1a2:	b9 ac 87 59 00       	mov    ecx,0x5987ac
  44d1a7:	a3 4c 28 62 0a       	mov    ds:0xa62284c,eax
  44d1ac:	e8 4f 49 11 00       	call   0x561b00
  44d1b1:	8b c8                	mov    ecx,eax
  44d1b3:	e8 58 93 0a 00       	call   0x4f6510
  44d1b8:	ba b8 87 59 00       	mov    edx,0x5987b8
  44d1bd:	b1 02                	mov    cl,0x2
  44d1bf:	e8 5c a6 0a 00       	call   0x4f7820
  44d1c4:	84 c0                	test   al,al
  44d1c6:	0f 84 bd 03 00 00    	je     0x44d589

  44e433:	5f                   	pop    edi
  44e434:	5e                   	pop    esi
  44e435:	5b                   	pop    ebx
  44e436:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  44e439:	33 cd                	xor    ecx,ebp
  44e43b:	e8 6e bc 13 00       	call   0x58a0ae
  44e440:	8b e5                	mov    esp,ebp
  44e442:	5d                   	pop    ebp
  44e443:	c3                   	ret
  44e444:	ba 16 c6 58 00       	mov    edx,0x58c616
  44e449:	b1 01                	mov    cl,0x1
  44e44b:	e8 d0 93 0a 00       	call   0x4f7820
  44e450:	84 c0                	test   al,al
  44e452:	74 d8                	je     0x44e42c

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
  458f70:	84 c0                	test   al,al
  458f72:	0f 84 e6 00 00 00    	je     0x45905e

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

  501d39:	8d 53 7e             	lea    edx,[ebx+0x7e]
  501d3c:	e8 7f 6b ff ff       	call   0x4f88c0
  501d41:	83 c4 0c             	add    esp,0xc
  501d44:	88 85 96 f9 ff ff    	mov    BYTE PTR [ebp-0x66a],al
  501d4a:	84 c0                	test   al,al
  501d4c:	0f 84 06 0e 00 00    	je     0x502b58
  501d52:	8b bd 68 f9 ff ff    	mov    edi,DWORD PTR [ebp-0x698]
  501d58:	8b 9d 7c f9 ff ff    	mov    ebx,DWORD PTR [ebp-0x684]
  501d5e:	eb 26                	jmp    0x501d86
  501d60:	ba a4 af 5a 00       	mov    edx,0x5aafa4
  501d65:	b1 02                	mov    cl,0x2
  501d67:	e8 b4 5a ff ff       	call   0x4f7820
  501d6c:	88 85 96 f9 ff ff    	mov    BYTE PTR [ebp-0x66a],al
  501d72:	84 c0                	test   al,al

  5086a8:	e8 83 b9 01 00       	call   0x524030
  5086ad:	8a d8                	mov    bl,al
  5086af:	90                   	nop
  5086b0:	68 00 04 00 00       	push   0x400
  5086b5:	6a 00                	push   0x0
  5086b7:	68 c0 6a 5e 00       	push   0x5e6ac0
  5086bc:	e8 9f 27 08 00       	call   0x58ae60
  5086c1:	83 c4 0c             	add    esp,0xc
  5086c4:	c6 05 e9 e0 b8 04 00 	mov    BYTE PTR ds:0x4b8e0e9,0x0
  5086cb:	ba 16 c6 58 00       	mov    edx,0x58c616
  5086d0:	b1 11                	mov    cl,0x11
  5086d2:	e8 49 f1 fe ff       	call   0x4f7820
  5086d7:	8b 35 3c bd 72 0a    	mov    esi,DWORD PTR ds:0xa72bd3c
  5086dd:	8b 3d 34 1c 6d 0a    	mov    edi,DWORD PTR ds:0xa6d1c34

  518421:	5d                   	pop    ebp
  518422:	c3                   	ret
  518423:	6a 01                	push   0x1
  518425:	51                   	push   ecx
  518426:	b9 5d 00 00 00       	mov    ecx,0x5d
  51842b:	e8 50 38 f0 ff       	call   0x41bc80
  518430:	83 c4 08             	add    esp,0x8
  518433:	85 c0                	test   eax,eax
  518435:	79 22                	jns    0x518459
  518437:	ba 5c cf 5a 00       	mov    edx,0x5acf5c
  51843c:	b1 02                	mov    cl,0x2
  51843e:	e8 dd f3 fd ff       	call   0x4f7820
  518443:	84 c0                	test   al,al
  518445:	0f 84 96 01 00 00    	je     0x5185e1

  518898:	0f 9f c1             	setg   cl
  51889b:	33 c0                	xor    eax,eax
  51889d:	85 d2                	test   edx,edx
  51889f:	0f 98 c0             	sets   al
  5188a2:	0b c8                	or     ecx,eax
  5188a4:	75 0f                	jne    0x5188b5
  5188a6:	69 c2 58 02 00 00    	imul   eax,edx,0x258
  5188ac:	f6 80 9c c7 5e 00 40 	test   BYTE PTR [eax+0x5ec79c],0x40
  5188b3:	75 28                	jne    0x5188dd
  5188b5:	ba a4 cf 5a 00       	mov    edx,0x5acfa4
  5188ba:	b1 02                	mov    cl,0x2
  5188bc:	e8 5f ef fd ff       	call   0x4f7820
  5188c1:	84 c0                	test   al,al
  5188c3:	0f 84 a8 06 00 00    	je     0x518f71

  51957d:	ff ff ff 
  519580:	50                   	push   eax
  519581:	83 c8 ff             	or     eax,0xffffffff
  519584:	8d 55 f4             	lea    edx,[ebp-0xc]
  519587:	8b c8                	mov    ecx,eax
  519589:	e8 72 73 f7 ff       	call   0x490900
  51958e:	83 c4 04             	add    esp,0x4
  519591:	3c 0c                	cmp    al,0xc
  519593:	74 22                	je     0x5195b7
  519595:	ba b4 d2 5a 00       	mov    edx,0x5ad2b4
  51959a:	b1 02                	mov    cl,0x2
  51959c:	e8 7f e2 fd ff       	call   0x4f7820
  5195a1:	84 c0                	test   al,al
  5195a3:	0f 84 e1 01 00 00    	je     0x51978a

  51981b:	0b c8                	or     ecx,eax
  51981d:	75 23                	jne    0x519842
  51981f:	69 c2 58 02 00 00    	imul   eax,edx,0x258
  519825:	f6 80 9c c7 5e 00 40 	test   BYTE PTR [eax+0x5ec79c],0x40
  51982c:	74 14                	je     0x519842
  51982e:	8b b5 3c bf ff ff    	mov    esi,DWORD PTR [ebp-0x40c4]
  519834:	8b 85 34 bf ff ff    	mov    eax,DWORD PTR [ebp-0x40cc]
  51983a:	89 b5 3c bf ff ff    	mov    DWORD PTR [ebp-0x40c4],esi
  519840:	eb 2a                	jmp    0x51986c
  519842:	ba 00 d4 5a 00       	mov    edx,0x5ad400
  519847:	b1 02                	mov    cl,0x2
  519849:	e8 d2 df fd ff       	call   0x4f7820
  51984e:	84 c0                	test   al,al
  519850:	0f 84 61 08 00 00    	je     0x51a0b7

  51a308:	89 44 24 14          	mov    DWORD PTR [esp+0x14],eax
  51a30c:	85 ff                	test   edi,edi
  51a30e:	75 32                	jne    0x51a342
  51a310:	85 c0                	test   eax,eax
  51a312:	75 2e                	jne    0x51a342
  51a314:	83 fe ff             	cmp    esi,0xffffffff
  51a317:	75 0a                	jne    0x51a323
  51a319:	b9 e4 d4 5a 00       	mov    ecx,0x5ad4e4
  51a31e:	e8 ed c1 fd ff       	call   0x4f6510
  51a323:	ba 1c d5 5a 00       	mov    edx,0x5ad51c
  51a328:	b1 02                	mov    cl,0x2
  51a32a:	e8 f1 d4 fd ff       	call   0x4f7820
  51a32f:	84 c0                	test   al,al
  51a331:	74 48                	je     0x51a37b

  51a4e8:	8b 44 24 14          	mov    eax,DWORD PTR [esp+0x14]
  51a4ec:	c6 44 24 2f 00       	mov    BYTE PTR [esp+0x2f],0x0
  51a4f1:	eb 07                	jmp    0x51a4fa
  51a4f3:	8b 45 08             	mov    eax,DWORD PTR [ebp+0x8]
  51a4f6:	89 44 24 14          	mov    DWORD PTR [esp+0x14],eax
  51a4fa:	85 ff                	test   edi,edi
  51a4fc:	74 04                	je     0x51a502
  51a4fe:	85 c0                	test   eax,eax
  51a500:	75 23                	jne    0x51a525
  51a502:	ba 54 d5 5a 00       	mov    edx,0x5ad554
  51a507:	b1 02                	mov    cl,0x2
  51a509:	e8 12 d3 fd ff       	call   0x4f7820
  51a50e:	84 c0                	test   al,al
  51a510:	0f 84 65 fe ff ff    	je     0x51a37b

  51a708:	89 44 24 14          	mov    DWORD PTR [esp+0x14],eax
  51a70c:	85 ff                	test   edi,edi
  51a70e:	75 36                	jne    0x51a746
  51a710:	85 c0                	test   eax,eax
  51a712:	75 32                	jne    0x51a746
  51a714:	83 fe ff             	cmp    esi,0xffffffff
  51a717:	75 0a                	jne    0x51a723
  51a719:	b9 a4 d5 5a 00       	mov    ecx,0x5ad5a4
  51a71e:	e8 ed bd fd ff       	call   0x4f6510
  51a723:	ba d0 d5 5a 00       	mov    edx,0x5ad5d0
  51a728:	b1 02                	mov    cl,0x2
  51a72a:	e8 f1 d0 fd ff       	call   0x4f7820
  51a72f:	84 c0                	test   al,al
  51a731:	0f 84 44 fc ff ff    	je     0x51a37b

  51a924:	8b 44 24 14          	mov    eax,DWORD PTR [esp+0x14]
  51a928:	c6 44 24 38 00       	mov    BYTE PTR [esp+0x38],0x0
  51a92d:	eb 07                	jmp    0x51a936
  51a92f:	8b 45 08             	mov    eax,DWORD PTR [ebp+0x8]
  51a932:	89 44 24 14          	mov    DWORD PTR [esp+0x14],eax
  51a936:	85 ff                	test   edi,edi
  51a938:	74 04                	je     0x51a93e
  51a93a:	85 c0                	test   eax,eax
  51a93c:	75 23                	jne    0x51a961
  51a93e:	ba 14 d6 5a 00       	mov    edx,0x5ad614
  51a943:	b1 02                	mov    cl,0x2
  51a945:	e8 d6 ce fd ff       	call   0x4f7820
  51a94a:	84 c0                	test   al,al
  51a94c:	0f 84 29 fa ff ff    	je     0x51a37b

  51bd01:	e8 ca 53 ee ff       	call   0x4010d0
  51bd06:	83 c4 0c             	add    esp,0xc
  51bd09:	8b ce                	mov    ecx,esi
  51bd0b:	eb 96                	jmp    0x51bca3
  51bd0d:	8b 8d 88 fb ff ff    	mov    ecx,DWORD PTR [ebp-0x478]
  51bd13:	85 c9                	test   ecx,ecx
  51bd15:	75 3e                	jne    0x51bd55
  51bd17:	85 db                	test   ebx,ebx
  51bd19:	75 3a                	jne    0x51bd55
  51bd1b:	ba c8 d9 5a 00       	mov    edx,0x5ad9c8
  51bd20:	b1 02                	mov    cl,0x2
  51bd22:	e8 f9 ba fd ff       	call   0x4f7820
  51bd27:	8a d8                	mov    bl,al
  51bd29:	84 db                	test   bl,bl

  51c159:	69 c7 58 02 00 00    	imul   eax,edi,0x258
  51c15f:	f6 80 9c c7 5e 00 40 	test   BYTE PTR [eax+0x5ec79c],0x40
  51c166:	0f 84 a3 00 00 00    	je     0x51c20f
  51c16c:	c6 05 ea c0 40 06 01 	mov    BYTE PTR ds:0x640c0ea,0x1
  51c173:	e8 68 da f7 ff       	call   0x499be0
  51c178:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [eax+eax*1+0x0]
  51c17f:	00 
  51c180:	b9 44 db 5a 00       	mov    ecx,0x5adb44
  51c185:	e8 86 a3 fd ff       	call   0x4f6510
  51c18a:	ba 7c db 5a 00       	mov    edx,0x5adb7c
  51c18f:	b1 06                	mov    cl,0x6
  51c191:	e8 8a b6 fd ff       	call   0x4f7820
  51c196:	8a d8                	mov    bl,al
  51c198:	84 db                	test   bl,bl

  51fa4c:	85 d2                	test   edx,edx
  51fa4e:	0f 98 c0             	sets   al
  51fa51:	0b c8                	or     ecx,eax
  51fa53:	75 0f                	jne    0x51fa64
  51fa55:	69 c2 58 02 00 00    	imul   eax,edx,0x258
  51fa5b:	f6 80 9c c7 5e 00 40 	test   BYTE PTR [eax+0x5ec79c],0x40
  51fa62:	75 2a                	jne    0x51fa8e
  51fa64:	b9 10 e2 5a 00       	mov    ecx,0x5ae210
  51fa69:	e8 a2 6a fd ff       	call   0x4f6510
  51fa6e:	ba 50 e2 5a 00       	mov    edx,0x5ae250
  51fa73:	b1 02                	mov    cl,0x2
  51fa75:	e8 a6 7d fd ff       	call   0x4f7820
  51fa7a:	84 c0                	test   al,al
  51fa7c:	0f 84 89 02 00 00    	je     0x51fd0b

  51fd38:	e8 03 3b 04 00       	call   0x563840
  51fd3d:	50                   	push   eax
  51fd3e:	6a 00                	push   0x0
  51fd40:	ba 30 00 00 00       	mov    edx,0x30
  51fd45:	83 c9 ff             	or     ecx,0xffffffff
  51fd48:	e8 43 ca fb ff       	call   0x4dc790
  51fd4d:	83 c4 08             	add    esp,0x8
  51fd50:	85 c0                	test   eax,eax
  51fd52:	0f 85 0c 04 00 00    	jne    0x520164
  51fd58:	ba f0 e3 5a 00       	mov    edx,0x5ae3f0
  51fd5d:	b1 06                	mov    cl,0x6
  51fd5f:	e8 bc 7a fd ff       	call   0x4f7820
  51fd64:	8a d8                	mov    bl,al
  51fd66:	84 db                	test   bl,bl

  5322b1:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  5322b7:	68 b4 13 5b 00       	push   0x5b13b4
  5322bc:	50                   	push   eax
  5322bd:	e8 0e ee ec ff       	call   0x4010d0
  5322c2:	83 c4 0c             	add    esp,0xc
  5322c5:	8d 8d f8 fb ff ff    	lea    ecx,[ebp-0x408]
  5322cb:	e8 f0 ed fc ff       	call   0x5010c0
  5322d0:	83 fb 03             	cmp    ebx,0x3
  5322d3:	0f 85 6d 02 00 00    	jne    0x532546
  5322d9:	ba f4 13 5b 00       	mov    edx,0x5b13f4
  5322de:	b1 06                	mov    cl,0x6
  5322e0:	e8 3b 55 fc ff       	call   0x4f7820
  5322e5:	84 c0                	test   al,al
  5322e7:	0f 84 ca fd ff ff    	je     0x5320b7

  532535:	5f                   	pop    edi
  532536:	5e                   	pop    esi
  532537:	5b                   	pop    ebx
  532538:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  53253b:	33 cd                	xor    ecx,ebp
  53253d:	e8 6c 7b 05 00       	call   0x58a0ae
  532542:	8b e5                	mov    esp,ebp
  532544:	5d                   	pop    ebp
  532545:	c3                   	ret
  532546:	ba 30 14 5b 00       	mov    edx,0x5b1430
  53254b:	b1 02                	mov    cl,0x2
  53254d:	e8 ce 52 fc ff       	call   0x4f7820
  532552:	84 c0                	test   al,al
  532554:	0f 84 5d fb ff ff    	je     0x5320b7

  543eeb:	b9 98 63 5b 00       	mov    ecx,0x5b6398
  543ef0:	a3 4c 2a 62 0a       	mov    ds:0xa622a4c,eax
  543ef5:	e8 06 dc 01 00       	call   0x561b00
  543efa:	8b c8                	mov    ecx,eax
  543efc:	e8 0f 26 fb ff       	call   0x4f6510
  543f01:	46                   	inc    esi
  543f02:	3b f7                	cmp    esi,edi
  543f04:	7c de                	jl     0x543ee4
  543f06:	8b b5 48 fa ff ff    	mov    esi,DWORD PTR [ebp-0x5b8]
  543f0c:	ba 16 c6 58 00       	mov    edx,0x58c616
  543f11:	b1 01                	mov    cl,0x1
  543f13:	e8 08 39 fb ff       	call   0x4f7820
  543f18:	84 c0                	test   al,al
  543f1a:	75 29                	jne    0x543f45

  545f17:	b9 98 63 5b 00       	mov    ecx,0x5b6398
  545f1c:	a3 4c 2a 62 0a       	mov    ds:0xa622a4c,eax
  545f21:	e8 da bb 01 00       	call   0x561b00
  545f26:	8b c8                	mov    ecx,eax
  545f28:	e8 e3 05 fb ff       	call   0x4f6510
  545f2d:	46                   	inc    esi
  545f2e:	3b f7                	cmp    esi,edi
  545f30:	7c de                	jl     0x545f10
  545f32:	8b b5 54 fa ff ff    	mov    esi,DWORD PTR [ebp-0x5ac]
  545f38:	ba 16 c6 58 00       	mov    edx,0x58c616
  545f3d:	b1 01                	mov    cl,0x1
  545f3f:	e8 dc 18 fb ff       	call   0x4f7820
  545f44:	84 c0                	test   al,al
  545f46:	75 42                	jne    0x545f8a

  546a65:	0a 
  546a66:	eb 3e                	jmp    0x546aa6
  546a68:	c7 44 24 28 18 fc ff 	mov    DWORD PTR [esp+0x28],0xfffffc18
  546a6f:	ff 
  546a70:	eb 0e                	jmp    0x546a80
  546a72:	85 db                	test   ebx,ebx
  546a74:	74 0a                	je     0x546a80
  546a76:	b9 18 69 5b 00       	mov    ecx,0x5b6918
  546a7b:	e8 90 fa fa ff       	call   0x4f6510
  546a80:	8d 54 24 68          	lea    edx,[esp+0x68]
  546a84:	b1 09                	mov    cl,0x9
  546a86:	e8 95 0d fb ff       	call   0x4f7820
  546a8b:	84 c0                	test   al,al
  546a8d:	74 2d                	je     0x546abc

  566bfb:	0f 9f c1             	setg   cl
  566bfe:	33 c0                	xor    eax,eax
  566c00:	85 db                	test   ebx,ebx
  566c02:	0f 98 c0             	sets   al
  566c05:	0b c8                	or     ecx,eax
  566c07:	75 0f                	jne    0x566c18
  566c09:	69 c3 58 02 00 00    	imul   eax,ebx,0x258
  566c0f:	f6 80 9c c7 5e 00 40 	test   BYTE PTR [eax+0x5ec79c],0x40
  566c16:	75 7a                	jne    0x566c92
  566c18:	ba a0 95 5d 00       	mov    edx,0x5d95a0
  566c1d:	b1 02                	mov    cl,0x2
  566c1f:	e8 fc 0b f9 ff       	call   0x4f7820
  566c24:	88 85 d7 fb ff ff    	mov    BYTE PTR [ebp-0x429],al
  566c2a:	84 c0                	test   al,al

  566f8e:	80 bd 40 ff ff ff 09 	cmp    BYTE PTR [ebp-0xc0],0x9
  566f95:	75 1c                	jne    0x566fb3
  566f97:	66 8b 45 a0          	mov    ax,WORD PTR [ebp-0x60]
  566f9b:	66 85 c0             	test   ax,ax
  566f9e:	74 13                	je     0x566fb3
  566fa0:	0f bf c8             	movsx  ecx,ax
  566fa3:	e8 c8 5a ea ff       	call   0x40ca70
  566fa8:	3d 18 fc ff ff       	cmp    eax,0xfffffc18
  566fad:	0f 85 b0 02 00 00    	jne    0x567263
  566fb3:	ba f4 95 5d 00       	mov    edx,0x5d95f4
  566fb8:	b1 02                	mov    cl,0x2
  566fba:	e8 61 08 f9 ff       	call   0x4f7820
  566fbf:	8b 15 34 1c 6d 0a    	mov    edx,DWORD PTR ds:0xa6d1c34
  566fc5:	8b 0d 3c bd 72 0a    	mov    ecx,DWORD PTR ds:0xa72bd3c

  570128:	8b 3d 50 c3 58 00    	mov    edi,DWORD PTR ds:0x58c350
  57012e:	83 c4 0c             	add    esp,0xc
  570131:	8d 84 24 28 0b 02 00 	lea    eax,[esp+0x20b28]
  570138:	68 30 a4 5d 00       	push   0x5da430
  57013d:	50                   	push   eax
  57013e:	ff d7                	call   edi
  570140:	83 c4 08             	add    esp,0x8
  570143:	85 c0                	test   eax,eax
  570145:	74 22                	je     0x570169
  570147:	ba 30 a4 5d 00       	mov    edx,0x5da430
  57014c:	b1 01                	mov    cl,0x1
  57014e:	e8 cd 76 f8 ff       	call   0x4f7820
  570153:	8b 15 34 1c 6d 0a    	mov    edx,DWORD PTR ds:0xa6d1c34
  570159:	8b 0d 3c bd 72 0a    	mov    ecx,DWORD PTR ds:0xa72bd3c

  570d25:	66 89 48 fe          	mov    WORD PTR [eax-0x2],cx
  570d29:	66 89 48 04          	mov    WORD PTR [eax+0x4],cx
  570d2d:	66 89 48 10          	mov    WORD PTR [eax+0x10],cx
  570d31:	66 89 48 0e          	mov    WORD PTR [eax+0xe],cx
  570d35:	89 48 18             	mov    DWORD PTR [eax+0x18],ecx
  570d38:	88 48 1c             	mov    BYTE PTR [eax+0x1c],cl
  570d3b:	83 c0 24             	add    eax,0x24
  570d3e:	3d ec a6 72 0a       	cmp    eax,0xa72a6ec
  570d43:	7c cb                	jl     0x570d10
  570d45:	ba ac a7 5d 00       	mov    edx,0x5da7ac
  570d4a:	b1 01                	mov    cl,0x1
  570d4c:	e8 cf 6a f8 ff       	call   0x4f7820
  570d51:	a1 34 1c 6d 0a       	mov    eax,ds:0xa6d1c34
  570d56:	8b d0                	mov    edx,eax

  570d4c:	e8 cf 6a f8 ff       	call   0x4f7820
  570d51:	a1 34 1c 6d 0a       	mov    eax,ds:0xa6d1c34
  570d56:	8b d0                	mov    edx,eax
  570d58:	89 44 24 14          	mov    DWORD PTR [esp+0x14],eax
  570d5c:	a1 3c bd 72 0a       	mov    eax,ds:0xa72bd3c
  570d61:	8b c8                	mov    ecx,eax
  570d63:	89 44 24 18          	mov    DWORD PTR [esp+0x18],eax
  570d67:	e8 b4 83 ea ff       	call   0x419120
  570d6c:	ba b8 a7 5d 00       	mov    edx,0x5da7b8
  570d71:	89 44 24 2c          	mov    DWORD PTR [esp+0x2c],eax
  570d75:	b1 10                	mov    cl,0x10
  570d77:	e8 a4 6a f8 ff       	call   0x4f7820
  570d7c:	84 c0                	test   al,al
  570d7e:	74 57                	je     0x570dd7

  5726b2:	e8 79 6c fd ff       	call   0x549330
  5726b7:	83 c4 04             	add    esp,0x4
  5726ba:	8d 84 24 28 0b 02 00 	lea    eax,[esp+0x20b28]
  5726c1:	68 3c aa 5d 00       	push   0x5daa3c
  5726c6:	50                   	push   eax
  5726c7:	ff d7                	call   edi
  5726c9:	83 c4 08             	add    esp,0x8
  5726cc:	85 c0                	test   eax,eax
  5726ce:	0f 84 83 00 00 00    	je     0x572757
  5726d4:	ba 4c aa 5d 00       	mov    edx,0x5daa4c
  5726d9:	b1 01                	mov    cl,0x1
  5726db:	e8 40 51 f8 ff       	call   0x4f7820
  5726e0:	84 c0                	test   al,al
  5726e2:	74 73                	je     0x572757

  573457:	83 c1 02             	add    ecx,0x2
  57345a:	84 d2                	test   dl,dl
  57345c:	75 e4                	jne    0x573442
  57345e:	33 c0                	xor    eax,eax
  573460:	eb 05                	jmp    0x573467
  573462:	1b c0                	sbb    eax,eax
  573464:	83 c8 01             	or     eax,0x1
  573467:	85 c0                	test   eax,eax
  573469:	75 4d                	jne    0x5734b8
  57346b:	ba 68 ab 5d 00       	mov    edx,0x5dab68
  573470:	b1 01                	mov    cl,0x1
  573472:	e8 a9 43 f8 ff       	call   0x4f7820
  573477:	84 c0                	test   al,al
  573479:	74 3d                	je     0x5734b8

  575125:	83 c1 02             	add    ecx,0x2
  575128:	84 d2                	test   dl,dl
  57512a:	75 e4                	jne    0x575110
  57512c:	33 c0                	xor    eax,eax
  57512e:	eb 05                	jmp    0x575135
  575130:	1b c0                	sbb    eax,eax
  575132:	83 c8 01             	or     eax,0x1
  575135:	85 c0                	test   eax,eax
  575137:	75 7a                	jne    0x5751b3
  575139:	ba 16 c6 58 00       	mov    edx,0x58c616
  57513e:	b1 04                	mov    cl,0x4
  575140:	e8 db 26 f8 ff       	call   0x4f7820
  575145:	84 c0                	test   al,al
  575147:	0f 84 72 78 00 00    	je     0x57c9bf

  57513e:	b1 04                	mov    cl,0x4
  575140:	e8 db 26 f8 ff       	call   0x4f7820
  575145:	84 c0                	test   al,al
  575147:	0f 84 72 78 00 00    	je     0x57c9bf
  57514d:	a1 34 1c 6d 0a       	mov    eax,ds:0xa6d1c34
  575152:	b9 90 ad 5d 00       	mov    ecx,0x5dad90
  575157:	8b 3d 3c bd 72 0a    	mov    edi,DWORD PTR ds:0xa72bd3c
  57515d:	89 44 24 14          	mov    DWORD PTR [esp+0x14],eax
  575161:	e8 aa 13 f8 ff       	call   0x4f6510
  575166:	ba 16 c6 58 00       	mov    edx,0x58c616
  57516b:	b1 04                	mov    cl,0x4
  57516d:	e8 ae 26 f8 ff       	call   0x4f7820
  575172:	84 c0                	test   al,al
  575174:	0f 84 45 78 00 00    	je     0x57c9bf

  57527b:	b9 b8 ad 5d 00       	mov    ecx,0x5dadb8
  575280:	e8 8b 12 f8 ff       	call   0x4f6510
  575285:	8d 84 24 28 0b 02 00 	lea    eax,[esp+0x20b28]
  57528c:	68 bc ad 5d 00       	push   0x5dadbc
  575291:	50                   	push   eax
  575292:	ff d7                	call   edi
  575294:	83 c4 08             	add    esp,0x8
  575297:	85 c0                	test   eax,eax
  575299:	74 62                	je     0x5752fd
  57529b:	ba 16 c6 58 00       	mov    edx,0x58c616
  5752a0:	b1 01                	mov    cl,0x1
  5752a2:	e8 79 25 f8 ff       	call   0x4f7820
  5752a7:	8b 15 34 1c 6d 0a    	mov    edx,DWORD PTR ds:0xa6d1c34
  5752ad:	8b 0d 3c bd 72 0a    	mov    ecx,DWORD PTR ds:0xa72bd3c

  575478:	8d 84 24 28 0b 02 00 	lea    eax,[esp+0x20b28]
  57547f:	68 e0 ad 5d 00       	push   0x5dade0
  575484:	50                   	push   eax
  575485:	ff d7                	call   edi
  575487:	83 c4 08             	add    esp,0x8
  57548a:	85 c0                	test   eax,eax
  57548c:	0f 84 07 01 00 00    	je     0x575599
  575492:	b9 e8 ad 5d 00       	mov    ecx,0x5dade8
  575497:	e8 74 10 f8 ff       	call   0x4f6510
  57549c:	ba 16 c6 58 00       	mov    edx,0x58c616
  5754a1:	b1 01                	mov    cl,0x1
  5754a3:	e8 78 23 f8 ff       	call   0x4f7820
  5754a8:	84 c0                	test   al,al
  5754aa:	0f 84 e9 00 00 00    	je     0x575599

  57615a:	8d 84 24 28 0b 02 00 	lea    eax,[esp+0x20b28]
  576161:	68 50 ae 5d 00       	push   0x5dae50
  576166:	50                   	push   eax
  576167:	ff d7                	call   edi
  576169:	83 c4 08             	add    esp,0x8
  57616c:	85 c0                	test   eax,eax
  57616e:	0f 84 a0 00 00 00    	je     0x576214
  576174:	b9 58 ae 5d 00       	mov    ecx,0x5dae58
  576179:	e8 92 03 f8 ff       	call   0x4f6510
  57617e:	ba 16 c6 58 00       	mov    edx,0x58c616
  576183:	b1 01                	mov    cl,0x1
  576185:	e8 96 16 f8 ff       	call   0x4f7820
  57618a:	84 c0                	test   al,al
  57618c:	0f 84 82 00 00 00    	je     0x576214

  576978:	68 70 af 5d 00       	push   0x5daf70
  57697d:	50                   	push   eax
  57697e:	ff d7                	call   edi
  576980:	83 c4 08             	add    esp,0x8
  576983:	85 c0                	test   eax,eax
  576985:	74 34                	je     0x5769bb
  576987:	e8 d4 57 f1 ff       	call   0x48c160
  57698c:	85 c0                	test   eax,eax
  57698e:	74 2b                	je     0x5769bb
  576990:	ba 4c aa 5d 00       	mov    edx,0x5daa4c
  576995:	b1 01                	mov    cl,0x1
  576997:	e8 84 0e f8 ff       	call   0x4f7820
  57699c:	84 c0                	test   al,al
  57699e:	74 1b                	je     0x5769bb

  576af4:	8b 0d 9c 1c 6d 0a    	mov    ecx,DWORD PTR ds:0xa6d1c9c
  576afa:	e8 c1 50 f7 ff       	call   0x4ebbc0
  576aff:	03 05 e4 b8 72 0a    	add    eax,DWORD PTR ds:0xa72b8e4
  576b05:	56                   	push   esi
  576b06:	50                   	push   eax
  576b07:	8d 84 24 30 0b 02 00 	lea    eax,[esp+0x20b30]
  576b0e:	68 a4 af 5d 00       	push   0x5dafa4
  576b13:	50                   	push   eax
  576b14:	e8 b7 a5 e8 ff       	call   0x4010d0
  576b19:	ba 16 c6 58 00       	mov    edx,0x58c616
  576b1e:	b1 01                	mov    cl,0x1
  576b20:	e8 fb 0c f8 ff       	call   0x4f7820
  576b25:	a1 34 1c 6d 0a       	mov    eax,ds:0xa6d1c34
  576b2a:	8b 35 3c bd 72 0a    	mov    esi,DWORD PTR ds:0xa72bd3c

  576f54:	e8 e7 a8 f0 ff       	call   0x481840
  576f59:	83 c4 08             	add    esp,0x8
  576f5c:	8d 84 24 28 0b 02 00 	lea    eax,[esp+0x20b28]
  576f63:	68 f8 af 5d 00       	push   0x5daff8
  576f68:	50                   	push   eax
  576f69:	ff d7                	call   edi
  576f6b:	83 c4 08             	add    esp,0x8
  576f6e:	85 c0                	test   eax,eax
  576f70:	74 22                	je     0x576f94
  576f72:	ba 16 c6 58 00       	mov    edx,0x58c616
  576f77:	b1 01                	mov    cl,0x1
  576f79:	e8 a2 08 f8 ff       	call   0x4f7820
  576f7e:	8b 15 34 1c 6d 0a    	mov    edx,DWORD PTR ds:0xa6d1c34
  576f84:	8b 0d 3c bd 72 0a    	mov    ecx,DWORD PTR ds:0xa72bd3c

  576f8c:	e8 7f 1c f8 ff       	call   0x4f8c10
  576f91:	83 c4 04             	add    esp,0x4
  576f94:	8d 84 24 28 0b 02 00 	lea    eax,[esp+0x20b28]
  576f9b:	68 fc af 5d 00       	push   0x5daffc
  576fa0:	50                   	push   eax
  576fa1:	ff d7                	call   edi
  576fa3:	83 c4 08             	add    esp,0x8
  576fa6:	85 c0                	test   eax,eax
  576fa8:	0f 84 b6 00 00 00    	je     0x577064
  576fae:	ba 16 c6 58 00       	mov    edx,0x58c616
  576fb3:	b1 01                	mov    cl,0x1
  576fb5:	e8 66 08 f8 ff       	call   0x4f7820
  576fba:	8b 15 34 1c 6d 0a    	mov    edx,DWORD PTR ds:0xa6d1c34
  576fc0:	8b 0d 3c bd 72 0a    	mov    ecx,DWORD PTR ds:0xa72bd3c

  57705a:	b9 18 b0 5d 00       	mov    ecx,0x5db018
  57705f:	e8 ac f4 f7 ff       	call   0x4f6510
  577064:	8d 84 24 28 0b 02 00 	lea    eax,[esp+0x20b28]
  57706b:	68 24 b0 5d 00       	push   0x5db024
  577070:	50                   	push   eax
  577071:	ff d7                	call   edi
  577073:	83 c4 08             	add    esp,0x8
  577076:	85 c0                	test   eax,eax
  577078:	0f 84 13 02 00 00    	je     0x577291
  57707e:	ba 16 c6 58 00       	mov    edx,0x58c616
  577083:	b1 01                	mov    cl,0x1
  577085:	e8 96 07 f8 ff       	call   0x4f7820
  57708a:	8b 15 34 1c 6d 0a    	mov    edx,DWORD PTR ds:0xa6d1c34
  577090:	8b 0d 3c bd 72 0a    	mov    ecx,DWORD PTR ds:0xa72bd3c

  5772b1:	fe c0                	inc    al
  5772b3:	a2 a9 b1 72 0a       	mov    ds:0xa72b1a9,al
  5772b8:	8d 84 24 28 0b 02 00 	lea    eax,[esp+0x20b28]
  5772bf:	68 44 b1 5d 00       	push   0x5db144
  5772c4:	50                   	push   eax
  5772c5:	ff d7                	call   edi
  5772c7:	83 c4 08             	add    esp,0x8
  5772ca:	85 c0                	test   eax,eax
  5772cc:	74 29                	je     0x5772f7
  5772ce:	ba 16 c6 58 00       	mov    edx,0x58c616
  5772d3:	b1 01                	mov    cl,0x1
  5772d5:	e8 46 05 f8 ff       	call   0x4f7820
  5772da:	8b 15 34 1c 6d 0a    	mov    edx,DWORD PTR ds:0xa6d1c34
  5772e0:	8b 0d 3c bd 72 0a    	mov    ecx,DWORD PTR ds:0xa72bd3c

  5777b7:	8d 84 24 28 0b 02 00 	lea    eax,[esp+0x20b28]
  5777be:	68 04 b2 5d 00       	push   0x5db204
  5777c3:	50                   	push   eax
  5777c4:	ff d7                	call   edi
  5777c6:	83 c4 08             	add    esp,0x8
  5777c9:	85 c0                	test   eax,eax
  5777cb:	0f 84 97 00 00 00    	je     0x577868
  5777d1:	b9 0c b2 5d 00       	mov    ecx,0x5db20c
  5777d6:	e8 35 ed f7 ff       	call   0x4f6510
  5777db:	ba 16 c6 58 00       	mov    edx,0x58c616
  5777e0:	b1 01                	mov    cl,0x1
  5777e2:	e8 39 00 f8 ff       	call   0x4f7820
  5777e7:	84 c0                	test   al,al
  5777e9:	0f 84 79 00 00 00    	je     0x577868

  577940:	83 c4 04             	add    esp,0x4
  577943:	e8 38 c3 f5 ff       	call   0x4d3c80
  577948:	8d 84 24 28 0b 02 00 	lea    eax,[esp+0x20b28]
  57794f:	68 28 b2 5d 00       	push   0x5db228
  577954:	50                   	push   eax
  577955:	ff d7                	call   edi
  577957:	83 c4 08             	add    esp,0x8
  57795a:	85 c0                	test   eax,eax
  57795c:	74 6c                	je     0x5779ca
  57795e:	ba 16 c6 58 00       	mov    edx,0x58c616
  577963:	b1 01                	mov    cl,0x1
  577965:	e8 b6 fe f7 ff       	call   0x4f7820
  57796a:	8b 15 34 1c 6d 0a    	mov    edx,DWORD PTR ds:0xa6d1c34
  577970:	8b 0d 3c bd 72 0a    	mov    ecx,DWORD PTR ds:0xa72bd3c

  5782a0:	8d 84 24 28 0b 02 00 	lea    eax,[esp+0x20b28]
  5782a7:	68 f0 b2 5d 00       	push   0x5db2f0
  5782ac:	50                   	push   eax
  5782ad:	ff d7                	call   edi
  5782af:	83 c4 08             	add    esp,0x8
  5782b2:	85 c0                	test   eax,eax
  5782b4:	74 64                	je     0x57831a
  5782b6:	b9 fc b2 5d 00       	mov    ecx,0x5db2fc
  5782bb:	e8 50 e2 f7 ff       	call   0x4f6510
  5782c0:	ba 16 c6 58 00       	mov    edx,0x58c616
  5782c5:	b1 01                	mov    cl,0x1
  5782c7:	e8 54 f5 f7 ff       	call   0x4f7820
  5782cc:	8b 15 34 1c 6d 0a    	mov    edx,DWORD PTR ds:0xa6d1c34
  5782d2:	8b 0d 3c bd 72 0a    	mov    ecx,DWORD PTR ds:0xa72bd3c

  5782c7:	e8 54 f5 f7 ff       	call   0x4f7820
  5782cc:	8b 15 34 1c 6d 0a    	mov    edx,DWORD PTR ds:0xa6d1c34
  5782d2:	8b 0d 3c bd 72 0a    	mov    ecx,DWORD PTR ds:0xa72bd3c
  5782d8:	e8 43 0e ea ff       	call   0x419120
  5782dd:	89 44 24 14          	mov    DWORD PTR [esp+0x14],eax
  5782e1:	83 f8 ff             	cmp    eax,0xffffffff
  5782e4:	74 34                	je     0x57831a
  5782e6:	b9 1c b3 5d 00       	mov    ecx,0x5db31c
  5782eb:	e8 20 e2 f7 ff       	call   0x4f6510
  5782f0:	ba 16 c6 58 00       	mov    edx,0x58c616
  5782f5:	b1 01                	mov    cl,0x1
  5782f7:	e8 24 f5 f7 ff       	call   0x4f7820
  5782fc:	8b 15 3c bd 72 0a    	mov    edx,DWORD PTR ds:0xa72bd3c
  578302:	8b 0d 34 1c 6d 0a    	mov    ecx,DWORD PTR ds:0xa6d1c34

  578aed:	be 01 00 00 00       	mov    esi,0x1
  578af2:	8b ce                	mov    ecx,esi
  578af4:	50                   	push   eax
  578af5:	a1 40 bd 72 0a       	mov    eax,ds:0xa72bd40
  578afa:	8d 52 05             	lea    edx,[edx+0x5]
  578afd:	83 c0 05             	add    eax,0x5
  578b00:	50                   	push   eax
  578b01:	e8 4a 1a ea ff       	call   0x41a550
  578b06:	83 c4 0c             	add    esp,0xc
  578b09:	ba 16 c6 58 00       	mov    edx,0x58c616
  578b0e:	b1 01                	mov    cl,0x1
  578b10:	e8 0b ed f7 ff       	call   0x4f7820
  578b15:	8b 15 34 1c 6d 0a    	mov    edx,DWORD PTR ds:0xa6d1c34
  578b1b:	8b 0d 3c bd 72 0a    	mov    ecx,DWORD PTR ds:0xa72bd3c

  578e26:	e8 15 8a f0 ff       	call   0x481840
  578e2b:	83 c4 08             	add    esp,0x8
  578e2e:	8d 84 24 28 0b 02 00 	lea    eax,[esp+0x20b28]
  578e35:	68 e0 b3 5d 00       	push   0x5db3e0
  578e3a:	50                   	push   eax
  578e3b:	ff d7                	call   edi
  578e3d:	83 c4 08             	add    esp,0x8
  578e40:	85 c0                	test   eax,eax
  578e42:	74 64                	je     0x578ea8
  578e44:	ba e0 b3 5d 00       	mov    edx,0x5db3e0
  578e49:	b1 01                	mov    cl,0x1
  578e4b:	e8 d0 e9 f7 ff       	call   0x4f7820
  578e50:	8b 15 34 1c 6d 0a    	mov    edx,DWORD PTR ds:0xa6d1c34
  578e56:	8d 84 24 40 ac 00 00 	lea    eax,[esp+0xac40]

  579816:	83 c1 02             	add    ecx,0x2
  579819:	84 d2                	test   dl,dl
  57981b:	75 e4                	jne    0x579801
  57981d:	33 c0                	xor    eax,eax
  57981f:	eb 05                	jmp    0x579826
  579821:	1b c0                	sbb    eax,eax
  579823:	83 c8 01             	or     eax,0x1
  579826:	85 c0                	test   eax,eax
  579828:	75 7f                	jne    0x5798a9
  57982a:	ba 16 c6 58 00       	mov    edx,0x58c616
  57982f:	b1 01                	mov    cl,0x1
  579831:	e8 ea df f7 ff       	call   0x4f7820
  579836:	8b 15 34 1c 6d 0a    	mov    edx,DWORD PTR ds:0xa6d1c34
  57983c:	8b 0d 3c bd 72 0a    	mov    ecx,DWORD PTR ds:0xa72bd3c

  579e6c:	5d                   	pop    ebp
  579e6d:	c3                   	ret
  579e6e:	83 f9 2c             	cmp    ecx,0x2c
  579e71:	75 0c                	jne    0x579e7f
  579e73:	8b cf                	mov    ecx,edi
  579e75:	e8 06 44 ff ff       	call   0x56e280
  579e7a:	e9 b6 fe ff ff       	jmp    0x579d35
  579e7f:	83 f9 30             	cmp    ecx,0x30
  579e82:	0f 85 80 0b 00 00    	jne    0x57aa08
  579e88:	ba 16 c6 58 00       	mov    edx,0x58c616
  579e8d:	b1 01                	mov    cl,0x1
  579e8f:	e8 8c d9 f7 ff       	call   0x4f7820
  579e94:	8b 15 34 1c 6d 0a    	mov    edx,DWORD PTR ds:0xa6d1c34
  579e9a:	8b 0d 3c bd 72 0a    	mov    ecx,DWORD PTR ds:0xa72bd3c

  57a69a:	33 cc                	xor    ecx,esp
  57a69c:	e8 0d fa 00 00       	call   0x58a0ae
  57a6a1:	8b e5                	mov    esp,ebp
  57a6a3:	5d                   	pop    ebp
  57a6a4:	c3                   	ret
  57a6a5:	b9 78 b8 5d 00       	mov    ecx,0x5db878
  57a6aa:	e8 f1 11 f8 ff       	call   0x4fb8a0
  57a6af:	84 c0                	test   al,al
  57a6b1:	74 45                	je     0x57a6f8
  57a6b3:	ba 16 c6 58 00       	mov    edx,0x58c616
  57a6b8:	b1 01                	mov    cl,0x1
  57a6ba:	e8 61 d1 f7 ff       	call   0x4f7820
  57a6bf:	8b 15 34 1c 6d 0a    	mov    edx,DWORD PTR ds:0xa6d1c34
  57a6c5:	8b 0d 3c bd 72 0a    	mov    ecx,DWORD PTR ds:0xa72bd3c

  57abc5:	33 cc                	xor    ecx,esp
  57abc7:	e8 e2 f4 00 00       	call   0x58a0ae
  57abcc:	8b e5                	mov    esp,ebp
  57abce:	5d                   	pop    ebp
  57abcf:	c3                   	ret
  57abd0:	83 f9 6f             	cmp    ecx,0x6f
  57abd3:	0f 85 c8 01 00 00    	jne    0x57ada1
  57abd9:	b9 1c ba 5d 00       	mov    ecx,0x5dba1c
  57abde:	e8 2d b9 f7 ff       	call   0x4f6510
  57abe3:	ba 16 c6 58 00       	mov    edx,0x58c616
  57abe8:	b1 01                	mov    cl,0x1
  57abea:	e8 31 cc f7 ff       	call   0x4f7820
  57abef:	8b 35 34 1c 6d 0a    	mov    esi,DWORD PTR ds:0xa6d1c34
  57abf5:	b9 2c ba 5d 00       	mov    ecx,0x5dba2c

  57abde:	e8 2d b9 f7 ff       	call   0x4f6510
  57abe3:	ba 16 c6 58 00       	mov    edx,0x58c616
  57abe8:	b1 01                	mov    cl,0x1
  57abea:	e8 31 cc f7 ff       	call   0x4f7820
  57abef:	8b 35 34 1c 6d 0a    	mov    esi,DWORD PTR ds:0xa6d1c34
  57abf5:	b9 2c ba 5d 00       	mov    ecx,0x5dba2c
  57abfa:	8b 3d 3c bd 72 0a    	mov    edi,DWORD PTR ds:0xa72bd3c
  57ac00:	89 74 24 14          	mov    DWORD PTR [esp+0x14],esi
  57ac04:	e8 07 b9 f7 ff       	call   0x4f6510
  57ac09:	ba 16 c6 58 00       	mov    edx,0x58c616
  57ac0e:	b1 01                	mov    cl,0x1
  57ac10:	e8 0b cc f7 ff       	call   0x4f7820
  57ac15:	8b d6                	mov    edx,esi
  57ac17:	8b cf                	mov    ecx,edi

  57b2da:	5e                   	pop    esi
  57b2db:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  57b2e2:	33 cc                	xor    ecx,esp
  57b2e4:	e8 c5 ed 00 00       	call   0x58a0ae
  57b2e9:	8b e5                	mov    esp,ebp
  57b2eb:	5d                   	pop    ebp
  57b2ec:	c3                   	ret
  57b2ed:	83 f9 6b             	cmp    ecx,0x6b
  57b2f0:	75 53                	jne    0x57b345
  57b2f2:	ba 16 c6 58 00       	mov    edx,0x58c616
  57b2f7:	b1 01                	mov    cl,0x1
  57b2f9:	e8 22 c5 f7 ff       	call   0x4f7820
  57b2fe:	8b 15 34 1c 6d 0a    	mov    edx,DWORD PTR ds:0xa6d1c34
  57b304:	8b 0d 3c bd 72 0a    	mov    ecx,DWORD PTR ds:0xa72bd3c

  57b332:	5e                   	pop    esi
  57b333:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  57b33a:	33 cc                	xor    ecx,esp
  57b33c:	e8 6d ed 00 00       	call   0x58a0ae
  57b341:	8b e5                	mov    esp,ebp
  57b343:	5d                   	pop    ebp
  57b344:	c3                   	ret
  57b345:	83 f9 78             	cmp    ecx,0x78
  57b348:	0f 85 b5 01 00 00    	jne    0x57b503
  57b34e:	ba 16 c6 58 00       	mov    edx,0x58c616
  57b353:	b1 04                	mov    cl,0x4
  57b355:	e8 c6 c4 f7 ff       	call   0x4f7820
  57b35a:	ff 35 34 1c 6d 0a    	push   DWORD PTR ds:0xa6d1c34
  57b360:	8b 15 3c bd 72 0a    	mov    edx,DWORD PTR ds:0xa72bd3c

  57db6c:	b9 a8 01 00 00       	mov    ecx,0x1a8
  57db71:	e8 da 5d fe ff       	call   0x563950
  57db76:	83 c4 04             	add    esp,0x4
  57db79:	e9 fa 00 00 00       	jmp    0x57dc78
  57db7e:	33 d2                	xor    edx,edx
  57db80:	8d 4a 78             	lea    ecx,[edx+0x78]
  57db83:	e8 98 6b fe ff       	call   0x564720
  57db88:	8b c8                	mov    ecx,eax
  57db8a:	e8 41 b5 f7 ff       	call   0x4f90d0
  57db8f:	ba bc c5 5d 00       	mov    edx,0x5dc5bc
  57db94:	b1 12                	mov    cl,0x12
  57db96:	e8 85 9c f7 ff       	call   0x4f7820
  57db9b:	84 c0                	test   al,al
  57db9d:	0f 84 d5 00 00 00    	je     0x57dc78

  4a311a:	85 c9                	test   ecx,ecx
  4a311c:	75 3b                	jne    0x4a3159
  4a311e:	6a 2c                	push   0x2c
  4a3120:	68 fe 00 00 00       	push   0xfe
  4a3125:	8d 45 90             	lea    eax,[ebp-0x70]
  4a3128:	68 ec d5 58 00       	push   0x58d5ec
  4a312d:	50                   	push   eax
  4a312e:	e8 9d df f5 ff       	call   0x4010d0
  4a3133:	83 c4 10             	add    esp,0x10
  4a3136:	8d 55 90             	lea    edx,[ebp-0x70]
  4a3139:	b9 ac eb 59 00       	mov    ecx,0x59ebac
  4a313e:	e8 fd 55 05 00       	call   0x4f8740
  4a3143:	84 c0                	test   al,al
  4a3145:	0f 84 eb 00 00 00    	je     0x4a3236

  4a3360:	6a 2d                	push   0x2d
  4a3362:	6a 16                	push   0x16
  4a3364:	8d 45 f0             	lea    eax,[ebp-0x10]
  4a3367:	c7 05 4c 2a 62 0a ff 	mov    DWORD PTR ds:0xa622a4c,0xffffffff
  4a336e:	ff ff ff 
  4a3371:	68 ec d5 58 00       	push   0x58d5ec
  4a3376:	50                   	push   eax
  4a3377:	e8 54 dd f5 ff       	call   0x4010d0
  4a337c:	83 c4 10             	add    esp,0x10
  4a337f:	8d 55 f0             	lea    edx,[ebp-0x10]
  4a3382:	b9 00 ec 59 00       	mov    ecx,0x59ec00
  4a3387:	e8 b4 53 05 00       	call   0x4f8740
  4a338c:	84 c0                	test   al,al
  4a338e:	0f 84 cc 00 00 00    	je     0x4a3460

  501d19:	85 db                	test   ebx,ebx
  501d1b:	0f 85 a4 00 00 00    	jne    0x501dc5
  501d21:	84 c0                	test   al,al
  501d23:	75 3b                	jne    0x501d60
  501d25:	53                   	push   ebx
  501d26:	8d 85 68 f9 ff ff    	lea    eax,[ebp-0x698]
  501d2c:	b9 8c af 5a 00       	mov    ecx,0x5aaf8c
  501d31:	50                   	push   eax
  501d32:	8d 85 7c f9 ff ff    	lea    eax,[ebp-0x684]
  501d38:	50                   	push   eax
  501d39:	8d 53 7e             	lea    edx,[ebx+0x7e]
  501d3c:	e8 7f 6b ff ff       	call   0x4f88c0
  501d41:	83 c4 0c             	add    esp,0xc
  501d44:	88 85 96 f9 ff ff    	mov    BYTE PTR [ebp-0x66a],al

  51db15:	5b                   	pop    ebx
  51db16:	8b e5                	mov    esp,ebp
  51db18:	5d                   	pop    ebp
  51db19:	c3                   	ret
  51db1a:	6a 0f                	push   0xf
  51db1c:	8d 45 f4             	lea    eax,[ebp-0xc]
  51db1f:	ba 34 00 00 00       	mov    edx,0x34
  51db24:	50                   	push   eax
  51db25:	8d 45 f8             	lea    eax,[ebp-0x8]
  51db28:	b9 f0 dd 5a 00       	mov    ecx,0x5addf0
  51db2d:	50                   	push   eax
  51db2e:	e8 8d ad fd ff       	call   0x4f88c0
  51db33:	83 c4 0c             	add    esp,0xc
  51db36:	84 c0                	test   al,al

  51dc1d:	e8 ee 88 fd ff       	call   0x4f6510
  51dc22:	8b e5                	mov    esp,ebp
  51dc24:	5d                   	pop    ebp
  51dc25:	c3                   	ret
  51dc26:	6a 07                	push   0x7
  51dc28:	8d 45 fc             	lea    eax,[ebp-0x4]
  51dc2b:	ba 34 00 00 00       	mov    edx,0x34
  51dc30:	50                   	push   eax
  51dc31:	8d 45 f8             	lea    eax,[ebp-0x8]
  51dc34:	b9 00 de 5a 00       	mov    ecx,0x5ade00
  51dc39:	50                   	push   eax
  51dc3a:	e8 81 ac fd ff       	call   0x4f88c0
  51dc3f:	83 c4 0c             	add    esp,0xc
  51dc42:	84 c0                	test   al,al

  4059ac:	e8 5f 0b 0f 00       	call   0x4f6510
  4059b1:	5f                   	pop    edi
  4059b2:	5e                   	pop    esi
  4059b3:	5b                   	pop    ebx
  4059b4:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  4059b7:	33 cd                	xor    ecx,ebp
  4059b9:	e8 f0 46 18 00       	call   0x58a0ae
  4059be:	8b e5                	mov    esp,ebp
  4059c0:	5d                   	pop    ebp
  4059c1:	c3                   	ret
  4059c2:	b9 14 d2 58 00       	mov    ecx,0x58d214
  4059c7:	e8 f4 31 0f 00       	call   0x4f8bc0
  4059cc:	84 c0                	test   al,al
  4059ce:	0f 84 fe 03 00 00    	je     0x405dd2

  566259:	8b e5                	mov    esp,ebp
  56625b:	5d                   	pop    ebp
  56625c:	c3                   	ret
  56625d:	83 f9 03             	cmp    ecx,0x3
  566260:	7f 13                	jg     0x566275
  566262:	b9 a0 cd 58 00       	mov    ecx,0x58cda0
  566267:	e8 a4 02 f9 ff       	call   0x4f6510
  56626c:	c6 85 e2 f6 ff ff 02 	mov    BYTE PTR [ebp-0x91e],0x2
  566273:	eb 07                	jmp    0x56627c
  566275:	c6 85 e2 f6 ff ff 00 	mov    BYTE PTR [ebp-0x91e],0x0
  56627c:	b9 70 93 5d 00       	mov    ecx,0x5d9370
  566281:	e8 3a 29 f9 ff       	call   0x4f8bc0
  566286:	84 c0                	test   al,al
  566288:	0f 84 40 ff ff ff    	je     0x5661ce

