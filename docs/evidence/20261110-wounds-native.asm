
# Original PE VA 004D7470..004D7963; subtract 00400000 for RVA.
  4d7470:	55                   	push   ebp
  4d7471:	8b ec                	mov    ebp,esp
  4d7473:	81 ec a4 00 00 00    	sub    esp,0xa4
  4d7479:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  4d747e:	33 c5                	xor    eax,ebp
  4d7480:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  4d7483:	53                   	push   ebx
  4d7484:	56                   	push   esi
  4d7485:	32 c0                	xor    al,al
  4d7487:	c7 85 78 ff ff ff ff 	mov    DWORD PTR [ebp-0x88],0xff
  4d748e:	00 00 00 
  4d7491:	57                   	push   edi
  4d7492:	88 85 7f ff ff ff    	mov    BYTE PTR [ebp-0x81],al
  4d7498:	33 ff                	xor    edi,edi
  4d749a:	66 0f 1f 44 00 00    	nop    WORD PTR [eax+eax*1+0x0]
  4d74a0:	8a 9f 30 b1 72 0a    	mov    bl,BYTE PTR [edi+0xa72b130]
  4d74a6:	84 db                	test   bl,bl
  4d74a8:	0f 84 58 04 00 00    	je     0x4d7906
  4d74ae:	8b 15 34 4a 35 06    	mov    edx,DWORD PTR ds:0x6354a34
  4d74b4:	0f 10 05 c0 4d 5a 00 	movups xmm0,XMMWORD PTR ds:0x5a4dc0
  4d74bb:	57                   	push   edi
  4d74bc:	69 ca e8 00 00 00    	imul   ecx,edx,0xe8
  4d74c2:	6b f2 0b             	imul   esi,edx,0xb
  4d74c5:	89 3c 95 b8 ac 35 06 	mov    DWORD PTR [edx*4+0x635acb8],edi
  4d74cc:	42                   	inc    edx
  4d74cd:	89 15 34 4a 35 06    	mov    DWORD PTR ds:0x6354a34,edx
  4d74d3:	0f b6 97 f4 b0 72 0a 	movzx  edx,BYTE PTR [edi+0xa72b0f4]
  4d74da:	c6 85 7f ff ff ff 01 	mov    BYTE PTR [ebp-0x81],0x1
  4d74e1:	83 c6 31             	add    esi,0x31
  4d74e4:	89 b5 74 ff ff ff    	mov    DWORD PTR [ebp-0x8c],esi
  4d74ea:	c7 81 e0 ef 34 06 34 	mov    DWORD PTR [ecx+0x634efe0],0x34
  4d74f1:	00 00 00 
  4d74f4:	8d 46 fd             	lea    eax,[esi-0x3]
  4d74f7:	89 81 e4 ef 34 06    	mov    DWORD PTR [ecx+0x634efe4],eax
  4d74fd:	a0 f0 4d 5a 00       	mov    al,ds:0x5a4df0
  4d7502:	c7 81 e8 ef 34 06 22 	mov    DWORD PTR [ecx+0x634efe8],0x122
  4d7509:	01 00 00 
  4d750c:	c7 81 ec ef 34 06 0e 	mov    DWORD PTR [ecx+0x634efec],0xe
  4d7513:	00 00 00 
  4d7516:	c7 81 d8 ef 34 06 00 	mov    DWORD PTR [ecx+0x634efd8],0x0
  4d751d:	00 00 00 
  4d7520:	0f 11 81 10 ef 34 06 	movups XMMWORD PTR [ecx+0x634ef10],xmm0
  4d7527:	0f 10 05 d0 4d 5a 00 	movups xmm0,XMMWORD PTR ds:0x5a4dd0
  4d752e:	0f 11 81 20 ef 34 06 	movups XMMWORD PTR [ecx+0x634ef20],xmm0
  4d7535:	0f 10 05 e0 4d 5a 00 	movups xmm0,XMMWORD PTR ds:0x5a4de0
  4d753c:	0f 11 81 30 ef 34 06 	movups XMMWORD PTR [ecx+0x634ef30],xmm0
  4d7543:	88 81 40 ef 34 06    	mov    BYTE PTR [ecx+0x634ef40],al
  4d7549:	0f b6 87 e0 b0 72 0a 	movzx  eax,BYTE PTR [edi+0xa72b0e0]
  4d7550:	0f b6 8f 1c b1 72 0a 	movzx  ecx,BYTE PTR [edi+0xa72b11c]
  4d7557:	50                   	push   eax
  4d7558:	0f b6 c3             	movzx  eax,bl
  4d755b:	50                   	push   eax
  4d755c:	e8 9f 63 02 00       	call   0x4fd900
  4d7561:	83 c4 0c             	add    esp,0xc
  4d7564:	6a 00                	push   0x0
  4d7566:	ff 15 0c c5 58 00    	call   DWORD PTR ds:0x58c50c
  4d756c:	83 c4 04             	add    esp,0x4
  4d756f:	89 85 60 ff ff ff    	mov    DWORD PTR [ebp-0xa0],eax
  4d7575:	8d 85 60 ff ff ff    	lea    eax,[ebp-0xa0]
  4d757b:	89 95 64 ff ff ff    	mov    DWORD PTR [ebp-0x9c],edx
  4d7581:	50                   	push   eax
  4d7582:	ff 15 14 c5 58 00    	call   DWORD PTR ds:0x58c514
  4d7588:	83 c4 04             	add    esp,0x4
  4d758b:	8b 48 04             	mov    ecx,DWORD PTR [eax+0x4]
  4d758e:	83 c1 45             	add    ecx,0x45
  4d7591:	0f af 08             	imul   ecx,DWORD PTR [eax]
  4d7594:	51                   	push   ecx
  4d7595:	ff 15 20 c5 58 00    	call   DWORD PTR ds:0x58c520
  4d759b:	83 c4 04             	add    esp,0x4
  4d759e:	8b d7                	mov    edx,edi
  4d75a0:	83 c9 ff             	or     ecx,0xffffffff
  4d75a3:	e8 08 fc ff ff       	call   0x4d71b0
  4d75a8:	50                   	push   eax
  4d75a9:	8d 45 90             	lea    eax,[ebp-0x70]
  4d75ac:	68 70 c6 58 00       	push   0x58c670
  4d75b1:	50                   	push   eax
  4d75b2:	e8 19 9b f2 ff       	call   0x4010d0
  4d75b7:	83 c4 0c             	add    esp,0xc
  4d75ba:	83 3d a0 28 6d 0a 00 	cmp    DWORD PTR ds:0xa6d28a0,0x0
  4d75c1:	74 2c                	je     0x4d75ef
  4d75c3:	ff 34 bd 04 b9 72 0a 	push   DWORD PTR [edi*4+0xa72b904]
  4d75ca:	0f b6 87 5c b1 72 0a 	movzx  eax,BYTE PTR [edi+0xa72b15c]
  4d75d1:	8b d7                	mov    edx,edi
  4d75d3:	50                   	push   eax
  4d75d4:	83 c9 ff             	or     ecx,0xffffffff
  4d75d7:	e8 d4 fb ff ff       	call   0x4d71b0
  4d75dc:	50                   	push   eax
  4d75dd:	57                   	push   edi
  4d75de:	8d 45 90             	lea    eax,[ebp-0x70]
  4d75e1:	68 9c 54 5a 00       	push   0x5a549c
  4d75e6:	50                   	push   eax
  4d75e7:	e8 e4 9a f2 ff       	call   0x4010d0
  4d75ec:	83 c4 18             	add    esp,0x18
  4d75ef:	80 bf 08 b1 72 0a 00 	cmp    BYTE PTR [edi+0xa72b108],0x0
  4d75f6:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4d75fb:	8b 35 f8 c1 58 00    	mov    esi,DWORD PTR ds:0x58c1f8
  4d7601:	74 06                	je     0x4d7609
  4d7603:	6a 57                	push   0x57
  4d7605:	6a 57                	push   0x57
  4d7607:	eb 0a                	jmp    0x4d7613
  4d7609:	68 ff 00 00 00       	push   0xff
  4d760e:	68 ff 00 00 00       	push   0xff
  4d7613:	68 ff 00 00 00       	push   0xff
  4d7618:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4d761b:	ff d6                	call   esi
  4d761d:	8b 9d 74 ff ff ff    	mov    ebx,DWORD PTR [ebp-0x8c]
  4d7623:	83 c4 10             	add    esp,0x10
  4d7626:	8b d3                	mov    edx,ebx
  4d7628:	b9 37 00 00 00       	mov    ecx,0x37
  4d762d:	6a 01                	push   0x1
  4d762f:	50                   	push   eax
  4d7630:	8d 45 90             	lea    eax,[ebp-0x70]
  4d7633:	50                   	push   eax
  4d7634:	e8 67 6f 03 00       	call   0x50e5a0
  4d7639:	83 c4 0c             	add    esp,0xc
  4d763c:	80 bf 08 b1 72 0a 00 	cmp    BYTE PTR [edi+0xa72b108],0x0
  4d7643:	74 2f                	je     0x4d7674
  4d7645:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4d764a:	6a 01                	push   0x1
  4d764c:	6a 57                	push   0x57
  4d764e:	6a 57                	push   0x57
  4d7650:	68 ff 00 00 00       	push   0xff
  4d7655:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4d7658:	ff d6                	call   esi
  4d765a:	83 c4 10             	add    esp,0x10
  4d765d:	8b d3                	mov    edx,ebx
  4d765f:	b9 1b 00 00 00       	mov    ecx,0x1b
  4d7664:	50                   	push   eax
  4d7665:	68 b4 54 5a 00       	push   0x5a54b4
  4d766a:	e8 31 6f 03 00       	call   0x50e5a0
  4d766f:	e9 31 01 00 00       	jmp    0x4d77a5
  4d7674:	0f b6 87 5c b1 72 0a 	movzx  eax,BYTE PTR [edi+0xa72b15c]
  4d767b:	85 c0                	test   eax,eax
  4d767d:	0f 84 25 01 00 00    	je     0x4d77a8
  4d7683:	48                   	dec    eax
  4d7684:	83 f8 63             	cmp    eax,0x63
  4d7687:	77 38                	ja     0x4d76c1
  4d7689:	0f b6 80 84 79 4d 00 	movzx  eax,BYTE PTR [eax+0x4d7984]
  4d7690:	ff 24 85 64 79 4d 00 	jmp    DWORD PTR [eax*4+0x4d7964]
  4d7697:	b8 06 00 00 00       	mov    eax,0x6
  4d769c:	eb 25                	jmp    0x4d76c3
  4d769e:	b8 01 00 00 00       	mov    eax,0x1
  4d76a3:	eb 1e                	jmp    0x4d76c3
  4d76a5:	b8 02 00 00 00       	mov    eax,0x2
  4d76aa:	eb 17                	jmp    0x4d76c3
  4d76ac:	b8 03 00 00 00       	mov    eax,0x3
  4d76b1:	eb 10                	jmp    0x4d76c3
  4d76b3:	b8 04 00 00 00       	mov    eax,0x4
  4d76b8:	eb 09                	jmp    0x4d76c3
  4d76ba:	b8 05 00 00 00       	mov    eax,0x5
  4d76bf:	eb 02                	jmp    0x4d76c3
  4d76c1:	33 c0                	xor    eax,eax
  4d76c3:	0f b6 94 40 bc e9 58 	movzx  edx,BYTE PTR [eax+eax*2+0x58e9bc]
  4d76ca:	00 
  4d76cb:	8d 73 09             	lea    esi,[ebx+0x9]
  4d76ce:	0f b6 8c 40 bd e9 58 	movzx  ecx,BYTE PTR [eax+eax*2+0x58e9bd]
  4d76d5:	00 
  4d76d6:	81 fa ff 00 00 00    	cmp    edx,0xff
  4d76dc:	0f b6 84 40 be e9 58 	movzx  eax,BYTE PTR [eax+eax*2+0x58e9be]
  4d76e3:	00 
  4d76e4:	0f 4f 95 78 ff ff ff 	cmovg  edx,DWORD PTR [ebp-0x88]
  4d76eb:	81 f9 ff 00 00 00    	cmp    ecx,0xff
  4d76f1:	0f 4f 8d 78 ff ff ff 	cmovg  ecx,DWORD PTR [ebp-0x88]
  4d76f8:	3d ff 00 00 00       	cmp    eax,0xff
  4d76fd:	0f 4f 85 78 ff ff ff 	cmovg  eax,DWORD PTR [ebp-0x88]
  4d7704:	50                   	push   eax
  4d7705:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4d770a:	51                   	push   ecx
  4d770b:	52                   	push   edx
  4d770c:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4d770f:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  4d7715:	50                   	push   eax
  4d7716:	8d 45 80             	lea    eax,[ebp-0x80]
  4d7719:	c7 45 80 1e 00 00 00 	mov    DWORD PTR [ebp-0x80],0x1e
  4d7720:	8b ce                	mov    ecx,esi
  4d7722:	89 5d 84             	mov    DWORD PTR [ebp-0x7c],ebx
  4d7725:	2b cb                	sub    ecx,ebx
  4d7727:	c7 45 88 09 00 00 00 	mov    DWORD PTR [ebp-0x78],0x9
  4d772e:	50                   	push   eax
  4d772f:	ff 35 10 bb 5b 06    	push   DWORD PTR ds:0x65bbb10
  4d7735:	41                   	inc    ecx
  4d7736:	89 4d 8c             	mov    DWORD PTR [ebp-0x74],ecx
  4d7739:	ff 15 e8 c1 58 00    	call   DWORD PTR ds:0x58c1e8
  4d773f:	83 c4 1c             	add    esp,0x1c
  4d7742:	c7 05 68 10 61 0a 00 	mov    DWORD PTR ds:0xa611068,0x0
  4d7749:	00 00 00 
  4d774c:	8b d3                	mov    edx,ebx
  4d774e:	b9 1e 00 00 00       	mov    ecx,0x1e
  4d7753:	6a 00                	push   0x0
  4d7755:	53                   	push   ebx
  4d7756:	6a 26                	push   0x26
  4d7758:	e8 e3 cb 03 00       	call   0x514340
  4d775d:	83 c4 0c             	add    esp,0xc
  4d7760:	8b d6                	mov    edx,esi
  4d7762:	b9 1e 00 00 00       	mov    ecx,0x1e
  4d7767:	ff 35 68 10 61 0a    	push   DWORD PTR ds:0xa611068
  4d776d:	56                   	push   esi
  4d776e:	6a 26                	push   0x26
  4d7770:	e8 cb cb 03 00       	call   0x514340
  4d7775:	83 c4 0c             	add    esp,0xc
  4d7778:	8b d3                	mov    edx,ebx
  4d777a:	b9 1e 00 00 00       	mov    ecx,0x1e
  4d777f:	ff 35 68 10 61 0a    	push   DWORD PTR ds:0xa611068
  4d7785:	56                   	push   esi
  4d7786:	6a 1e                	push   0x1e
  4d7788:	e8 b3 cb 03 00       	call   0x514340
  4d778d:	83 c4 0c             	add    esp,0xc
  4d7790:	8b d3                	mov    edx,ebx
  4d7792:	b9 26 00 00 00       	mov    ecx,0x26
  4d7797:	ff 35 68 10 61 0a    	push   DWORD PTR ds:0xa611068
  4d779d:	56                   	push   esi
  4d779e:	6a 26                	push   0x26
  4d77a0:	e8 9b cb 03 00       	call   0x514340
  4d77a5:	83 c4 0c             	add    esp,0xc
  4d77a8:	8b 14 bd 54 b9 72 0a 	mov    edx,DWORD PTR [edi*4+0xa72b954]
  4d77af:	33 db                	xor    ebx,ebx
  4d77b1:	b8 01 00 00 00       	mov    eax,0x1
  4d77b6:	8d 4b 10             	lea    ecx,[ebx+0x10]
  4d77b9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [eax+0x0]
  4d77c0:	85 d0                	test   eax,edx
  4d77c2:	74 01                	je     0x4d77c5
  4d77c4:	43                   	inc    ebx
  4d77c5:	d1 c0                	rol    eax,1
  4d77c7:	83 e9 01             	sub    ecx,0x1
  4d77ca:	75 f4                	jne    0x4d77c0
  4d77cc:	0f b6 87 1c b1 72 0a 	movzx  eax,BYTE PTR [edi+0xa72b11c]
  4d77d3:	0f b6 97 e0 b0 72 0a 	movzx  edx,BYTE PTR [edi+0xa72b0e0]
  4d77da:	0f b6 8f 30 b1 72 0a 	movzx  ecx,BYTE PTR [edi+0xa72b130]
  4d77e1:	50                   	push   eax
  4d77e2:	e8 29 11 00 00       	call   0x4d8910
  4d77e7:	83 c4 04             	add    esp,0x4
  4d77ea:	b9 01 00 00 00       	mov    ecx,0x1
  4d77ef:	33 f6                	xor    esi,esi
  4d77f1:	8d 56 10             	lea    edx,[esi+0x10]
  4d77f4:	85 c1                	test   ecx,eax
  4d77f6:	74 01                	je     0x4d77f9
  4d77f8:	46                   	inc    esi
  4d77f9:	d1 c1                	rol    ecx,1
  4d77fb:	83 ea 01             	sub    edx,0x1
  4d77fe:	75 f4                	jne    0x4d77f4
  4d7800:	85 db                	test   ebx,ebx
  4d7802:	0f 84 82 00 00 00    	je     0x4d788a
  4d7808:	8b c3                	mov    eax,ebx
  4d780a:	b9 32 00 00 00       	mov    ecx,0x32
  4d780f:	99                   	cdq
  4d7810:	f7 fe                	idiv   esi
  4d7812:	6b c0 32             	imul   eax,eax,0x32
  4d7815:	2b c8                	sub    ecx,eax
  4d7817:	e8 b4 58 03 00       	call   0x50d0d0
  4d781c:	66 0f 6e cb          	movd   xmm1,ebx
  4d7820:	83 ec 08             	sub    esp,0x8
  4d7823:	66 0f 6e c6          	movd   xmm0,esi
  4d7827:	0f 5b c9             	cvtdq2ps xmm1,xmm1
  4d782a:	a3 d0 10 61 0a       	mov    ds:0xa6110d0,eax
  4d782f:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4d7832:	f3 0f 5e c8          	divss  xmm1,xmm0
  4d7836:	f3 0f 59 0d 08 d6 5d 	mulss  xmm1,DWORD PTR ds:0x5dd608
  4d783d:	00 
  4d783e:	0f 5a c1             	cvtps2pd xmm0,xmm1
  4d7841:	f2 0f 11 85 68 ff ff 	movsd  QWORD PTR [ebp-0x98],xmm0
  4d7848:	ff 
  4d7849:	dd 85 68 ff ff ff    	fld    QWORD PTR [ebp-0x98]
  4d784f:	dd 1c 24             	fstp   QWORD PTR [esp]
  4d7852:	e8 85 3d 0b 00       	call   0x58b5dc
  4d7857:	8b b5 74 ff ff ff    	mov    esi,DWORD PTR [ebp-0x8c]
  4d785d:	bb 64 00 00 00       	mov    ebx,0x64
  4d7862:	dd 9d 68 ff ff ff    	fstp   QWORD PTR [ebp-0x98]
  4d7868:	f2 0f 2c 85 68 ff ff 	cvttsd2si eax,QWORD PTR [ebp-0x98]
  4d786f:	ff 
  4d7870:	8b d6                	mov    edx,esi
  4d7872:	b9 a9 01 00 00       	mov    ecx,0x1a9
  4d7877:	83 f8 64             	cmp    eax,0x64
  4d787a:	0f 4f c3             	cmovg  eax,ebx
  4d787d:	50                   	push   eax
  4d787e:	6a 14                	push   0x14
  4d7880:	e8 eb 58 03 00       	call   0x50d170
  4d7885:	83 c4 10             	add    esp,0x10
  4d7888:	eb 0b                	jmp    0x4d7895
  4d788a:	8b b5 74 ff ff ff    	mov    esi,DWORD PTR [ebp-0x8c]
  4d7890:	bb 64 00 00 00       	mov    ebx,0x64
  4d7895:	8a 87 44 b1 72 0a    	mov    al,BYTE PTR [edi+0xa72b144]
  4d789b:	84 c0                	test   al,al
  4d789d:	74 67                	je     0x4d7906
  4d789f:	0f b6 c0             	movzx  eax,al
  4d78a2:	83 ec 08             	sub    esp,0x8
  4d78a5:	c7 05 d0 10 61 0a ff 	mov    DWORD PTR ds:0xa6110d0,0xffffffff
  4d78ac:	ff ff ff 
  4d78af:	66 0f 6e c0          	movd   xmm0,eax
  4d78b3:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  4d78b6:	f3 0f 5e 05 70 d5 5d 	divss  xmm0,DWORD PTR ds:0x5dd570
  4d78bd:	00 
  4d78be:	f3 0f 59 05 08 d6 5d 	mulss  xmm0,DWORD PTR ds:0x5dd608
  4d78c5:	00 
  4d78c6:	0f 5a c0             	cvtps2pd xmm0,xmm0
  4d78c9:	f2 0f 11 85 68 ff ff 	movsd  QWORD PTR [ebp-0x98],xmm0
  4d78d0:	ff 
  4d78d1:	dd 85 68 ff ff ff    	fld    QWORD PTR [ebp-0x98]
  4d78d7:	dd 1c 24             	fstp   QWORD PTR [esp]
  4d78da:	e8 fd 3c 0b 00       	call   0x58b5dc
  4d78df:	dd 9d 68 ff ff ff    	fstp   QWORD PTR [ebp-0x98]
  4d78e5:	f2 0f 2c 85 68 ff ff 	cvttsd2si eax,QWORD PTR [ebp-0x98]
  4d78ec:	ff 
  4d78ed:	8d 56 ff             	lea    edx,[esi-0x1]
  4d78f0:	b9 59 01 00 00       	mov    ecx,0x159
  4d78f5:	83 f8 64             	cmp    eax,0x64
  4d78f8:	0f 4f c3             	cmovg  eax,ebx
  4d78fb:	50                   	push   eax
  4d78fc:	6a 32                	push   0x32
  4d78fe:	e8 6d 58 03 00       	call   0x50d170
  4d7903:	83 c4 10             	add    esp,0x10
  4d7906:	47                   	inc    edi
  4d7907:	83 ff 14             	cmp    edi,0x14
  4d790a:	0f 8c 90 fb ff ff    	jl     0x4d74a0
  4d7910:	8a 85 7f ff ff ff    	mov    al,BYTE PTR [ebp-0x81]
  4d7916:	84 c0                	test   al,al
  4d7918:	75 38                	jne    0x4d7952
  4d791a:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4d791f:	6a 01                	push   0x1
  4d7921:	68 ab 00 00 00       	push   0xab
  4d7926:	68 ab 00 00 00       	push   0xab
  4d792b:	68 ab 00 00 00       	push   0xab
  4d7930:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4d7933:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  4d7939:	83 c4 10             	add    esp,0x10
  4d793c:	ba 3c 00 00 00       	mov    edx,0x3c
  4d7941:	50                   	push   eax
  4d7942:	68 b8 54 5a 00       	push   0x5a54b8
  4d7947:	8d 4a d8             	lea    ecx,[edx-0x28]
  4d794a:	e8 51 6c 03 00       	call   0x50e5a0
  4d794f:	83 c4 0c             	add    esp,0xc
  4d7952:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  4d7955:	5f                   	pop    edi
  4d7956:	5e                   	pop    esi
  4d7957:	33 cd                	xor    ecx,ebp
  4d7959:	5b                   	pop    ebx
  4d795a:	e8 4f 27 0b 00       	call   0x58a0ae
  4d795f:	8b e5                	mov    esp,ebp
  4d7961:	5d                   	pop    ebp
  4d7962:	c3                   	ret

# Original PE VA 004D79F0..004D7CA6; subtract 00400000 for RVA.
  4d79f0:	55                   	push   ebp
  4d79f1:	8b ec                	mov    ebp,esp
  4d79f3:	83 ec 14             	sub    esp,0x14
  4d79f6:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  4d79fb:	33 c5                	xor    eax,ebp
  4d79fd:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  4d7a00:	53                   	push   ebx
  4d7a01:	56                   	push   esi
  4d7a02:	57                   	push   edi
  4d7a03:	33 d2                	xor    edx,edx
  4d7a05:	b9 2c 52 78 0a       	mov    ecx,0xa78522c
  4d7a0a:	66 0f 1f 44 00 00    	nop    WORD PTR [eax+eax*1+0x0]
  4d7a10:	8a 01                	mov    al,BYTE PTR [ecx]
  4d7a12:	8d 52 01             	lea    edx,[edx+0x1]
  4d7a15:	81 c1 48 0c 00 00    	add    ecx,0xc48
  4d7a1b:	88 82 6f ef 80 0a    	mov    BYTE PTR [edx+0xa80ef6f],al
  4d7a21:	81 f9 2c 76 7e 0a    	cmp    ecx,0xa7e762c
  4d7a27:	7c e7                	jl     0x4d7a10
  4d7a29:	b9 5c 41 59 00       	mov    ecx,0x59415c
  4d7a2e:	e8 bd 36 03 00       	call   0x50b0f0
  4d7a33:	0f 28 05 c0 da 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5ddac0
  4d7a3a:	8d 45 ec             	lea    eax,[ebp-0x14]
  4d7a3d:	50                   	push   eax
  4d7a3e:	ff 35 14 20 5c 0a    	push   DWORD PTR ds:0xa5c2014
  4d7a44:	0f 11 45 ec          	movups XMMWORD PTR [ebp-0x14],xmm0
  4d7a48:	50                   	push   eax
  4d7a49:	ff 35 10 bb 5b 06    	push   DWORD PTR ds:0x65bbb10
  4d7a4f:	ff 15 04 c2 58 00    	call   DWORD PTR ds:0x58c204
  4d7a55:	83 c4 10             	add    esp,0x10
  4d7a58:	c7 05 d8 bc 5b 06 00 	mov    DWORD PTR ds:0x65bbcd8,0x0
  4d7a5f:	00 00 00 
  4d7a62:	b9 7c d5 59 00       	mov    ecx,0x59d57c
  4d7a67:	e8 84 36 03 00       	call   0x50b0f0
  4d7a6c:	e8 7f 3f 03 00       	call   0x50b9f0
  4d7a71:	e8 8a 60 02 00       	call   0x4fdb00
  4d7a76:	8b 35 10 bb 5b 06    	mov    esi,DWORD PTR ds:0x65bbb10
  4d7a7c:	f6 06 02             	test   BYTE PTR [esi],0x2
  4d7a7f:	74 10                	je     0x4d7a91
  4d7a81:	56                   	push   esi
  4d7a82:	ff 15 b4 c1 58 00    	call   DWORD PTR ds:0x58c1b4
  4d7a88:	8b 35 10 bb 5b 06    	mov    esi,DWORD PTR ds:0x65bbb10
  4d7a8e:	83 c4 04             	add    esp,0x4
  4d7a91:	8b 46 10             	mov    eax,DWORD PTR [esi+0x10]
  4d7a94:	99                   	cdq
  4d7a95:	83 e2 03             	and    edx,0x3
  4d7a98:	03 c2                	add    eax,edx
  4d7a9a:	c1 f8 02             	sar    eax,0x2
  4d7a9d:	69 c8 90 01 00 00    	imul   ecx,eax,0x190
  4d7aa3:	f6 06 02             	test   BYTE PTR [esi],0x2
  4d7aa6:	8b 46 14             	mov    eax,DWORD PTR [esi+0x14]
  4d7aa9:	8b bc 01 70 0a 00 00 	mov    edi,DWORD PTR [ecx+eax*1+0xa70]
  4d7ab0:	74 0a                	je     0x4d7abc
  4d7ab2:	56                   	push   esi
  4d7ab3:	ff 15 b8 c1 58 00    	call   DWORD PTR ds:0x58c1b8
  4d7ab9:	83 c4 04             	add    esp,0x4
  4d7abc:	b9 d0 54 5a 00       	mov    ecx,0x5a54d0
  4d7ac1:	89 3d 20 b6 5b 06    	mov    DWORD PTR ds:0x65bb620,edi
  4d7ac7:	e8 34 45 f3 ff       	call   0x40c000
  4d7acc:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4d7ad1:	8b 35 f8 c1 58 00    	mov    esi,DWORD PTR ds:0x58c1f8
  4d7ad7:	6a 64                	push   0x64
  4d7ad9:	68 44 02 00 00       	push   0x244
  4d7ade:	68 f4 01 00 00       	push   0x1f4
  4d7ae3:	6a 28                	push   0x28
  4d7ae5:	6a 0a                	push   0xa
  4d7ae7:	6a 54                	push   0x54
  4d7ae9:	68 fc 00 00 00       	push   0xfc
  4d7aee:	68 fc 00 00 00       	push   0xfc
  4d7af3:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4d7af6:	ff d6                	call   esi
  4d7af8:	83 c4 10             	add    esp,0x10
  4d7afb:	ba 16 c6 58 00       	mov    edx,0x58c616
  4d7b00:	8b c8                	mov    ecx,eax
  4d7b02:	e8 89 7c ff ff       	call   0x4cf790
  4d7b07:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4d7b0c:	83 c4 14             	add    esp,0x14
  4d7b0f:	6a 01                	push   0x1
  4d7b11:	6a 00                	push   0x0
  4d7b13:	68 16 c6 58 00       	push   0x58c616
  4d7b18:	68 ff 00 00 00       	push   0xff
  4d7b1d:	68 ff 00 00 00       	push   0xff
  4d7b22:	68 ff 00 00 00       	push   0xff
  4d7b27:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4d7b2a:	ff d6                	call   esi
  4d7b2c:	83 c4 10             	add    esp,0x10
  4d7b2f:	8b c8                	mov    ecx,eax
  4d7b31:	e8 ea 7b ff ff       	call   0x4cf720
  4d7b36:	83 c4 0c             	add    esp,0xc
  4d7b39:	c7 05 9c 4a 35 06 01 	mov    DWORD PTR ds:0x6354a9c,0x1
  4d7b40:	00 00 00 
  4d7b43:	c7 05 a0 4a 35 06 01 	mov    DWORD PTR ds:0x6354aa0,0x1
  4d7b4a:	00 00 00 
  4d7b4d:	e8 1e f9 ff ff       	call   0x4d7470
  4d7b52:	a1 34 4a 35 06       	mov    eax,ds:0x6354a34
  4d7b57:	ba 0a 00 00 00       	mov    edx,0xa
  4d7b5c:	68 c8 50 59 00       	push   0x5950c8
  4d7b61:	68 8b 01 00 00       	push   0x18b
  4d7b66:	a3 bc 4a 35 06       	mov    ds:0x6354abc,eax
  4d7b6b:	8d 4a 11             	lea    ecx,[edx+0x11]
  4d7b6e:	e8 7d 7f ff ff       	call   0x4cfaf0
  4d7b73:	83 c4 04             	add    esp,0x4
  4d7b76:	ba 16 c6 58 00       	mov    edx,0x58c616
  4d7b7b:	b9 e0 54 5a 00       	mov    ecx,0x5a54e0
  4d7b80:	e8 0b 4f f6 ff       	call   0x43ca90
  4d7b85:	83 c4 04             	add    esp,0x4
  4d7b88:	68 78 f9 58 00       	push   0x58f978
  4d7b8d:	68 20 4e 5a 00       	push   0x5a4e20
  4d7b92:	ff 15 78 c4 58 00    	call   DWORD PTR ds:0x58c478
  4d7b98:	8b 35 d8 c4 58 00    	mov    esi,DWORD PTR ds:0x58c4d8
  4d7b9e:	8b f8                	mov    edi,eax
  4d7ba0:	57                   	push   edi
  4d7ba1:	6a 01                	push   0x1
  4d7ba3:	68 90 01 00 00       	push   0x190
  4d7ba8:	68 20 4a 35 06       	push   0x6354a20
  4d7bad:	ff d6                	call   esi
  4d7baf:	57                   	push   edi
  4d7bb0:	6a 01                	push   0x1
  4d7bb2:	68 a0 5a 00 00       	push   0x5aa0
  4d7bb7:	68 10 ef 34 06       	push   0x634ef10
  4d7bbc:	ff d6                	call   esi
  4d7bbe:	57                   	push   edi
  4d7bbf:	ff 15 b4 c4 58 00    	call   DWORD PTR ds:0x58c4b4
  4d7bc5:	8b 1d a8 c4 58 00    	mov    ebx,DWORD PTR ds:0x58c4a8
  4d7bcb:	83 c4 2c             	add    esp,0x2c
  4d7bce:	66 90                	xchg   ax,ax
  4d7bd0:	e8 4b 95 ff ff       	call   0x4d1120
  4d7bd5:	8b f0                	mov    esi,eax
  4d7bd7:	83 fe ff             	cmp    esi,0xffffffff
  4d7bda:	74 f4                	je     0x4d7bd0
  4d7bdc:	83 fe 64             	cmp    esi,0x64
  4d7bdf:	7d 6a                	jge    0x4d7c4b
  4d7be1:	85 f6                	test   esi,esi
  4d7be3:	78 66                	js     0x4d7c4b
  4d7be5:	69 c6 e8 00 00 00    	imul   eax,esi,0xe8
  4d7beb:	8b 80 d8 ef 34 06    	mov    eax,DWORD PTR [eax+0x634efd8]
  4d7bf1:	83 f8 1b             	cmp    eax,0x1b
  4d7bf4:	74 50                	je     0x4d7c46
  4d7bf6:	3d 23 04 00 00       	cmp    eax,0x423
  4d7bfb:	75 4e                	jne    0x4d7c4b
  4d7bfd:	b9 2c 5d 59 00       	mov    ecx,0x595d2c
  4d7c02:	e8 a9 7b 00 00       	call   0x4df7b0
  4d7c07:	68 f8 f1 58 00       	push   0x58f1f8
  4d7c0c:	68 20 4e 5a 00       	push   0x5a4e20
  4d7c11:	ff 15 78 c4 58 00    	call   DWORD PTR ds:0x58c478
  4d7c17:	8b f8                	mov    edi,eax
  4d7c19:	57                   	push   edi
  4d7c1a:	6a 01                	push   0x1
  4d7c1c:	68 90 01 00 00       	push   0x190
  4d7c21:	68 20 4a 35 06       	push   0x6354a20
  4d7c26:	ff d3                	call   ebx
  4d7c28:	57                   	push   edi
  4d7c29:	6a 01                	push   0x1
  4d7c2b:	68 a0 5a 00 00       	push   0x5aa0
  4d7c30:	68 10 ef 34 06       	push   0x634ef10
  4d7c35:	ff d3                	call   ebx
  4d7c37:	57                   	push   edi
  4d7c38:	ff 15 b4 c4 58 00    	call   DWORD PTR ds:0x58c4b4
  4d7c3e:	89 35 b0 4a 35 06    	mov    DWORD PTR ds:0x6354ab0,esi
  4d7c44:	eb 85                	jmp    0x4d7bcb
  4d7c46:	83 cf ff             	or     edi,0xffffffff
  4d7c49:	eb 07                	jmp    0x4d7c52
  4d7c4b:	8b 3c b5 b8 ac 35 06 	mov    edi,DWORD PTR [esi*4+0x635acb8]
  4d7c52:	b9 7c d5 59 00       	mov    ecx,0x59d57c
  4d7c57:	c7 05 d8 bc 5b 06 01 	mov    DWORD PTR ds:0x65bbcd8,0x1
  4d7c5e:	00 00 00 
  4d7c61:	e8 fa 33 03 00       	call   0x50b060
  4d7c66:	33 f6                	xor    esi,esi
  4d7c68:	ba 2c 52 78 0a       	mov    edx,0xa78522c
  4d7c6d:	0f 1f 00             	nop    DWORD PTR [eax]
  4d7c70:	8a 8e 70 ef 80 0a    	mov    cl,BYTE PTR [esi+0xa80ef70]
  4d7c76:	8d 76 01             	lea    esi,[esi+0x1]
  4d7c79:	88 0a                	mov    BYTE PTR [edx],cl
  4d7c7b:	81 c2 48 0c 00 00    	add    edx,0xc48
  4d7c81:	81 fa 2c 76 7e 0a    	cmp    edx,0xa7e762c
  4d7c87:	7c e7                	jl     0x4d7c70
  4d7c89:	e8 d2 5d 03 00       	call   0x50da60
  4d7c8e:	e8 5d 42 f3 ff       	call   0x40bef0
  4d7c93:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  4d7c96:	8b c7                	mov    eax,edi
  4d7c98:	5f                   	pop    edi
  4d7c99:	5e                   	pop    esi
  4d7c9a:	33 cd                	xor    ecx,ebp
  4d7c9c:	5b                   	pop    ebx
  4d7c9d:	e8 0c 24 0b 00       	call   0x58a0ae
  4d7ca2:	8b e5                	mov    esp,ebp
  4d7ca4:	5d                   	pop    ebp
  4d7ca5:	c3                   	ret

# Original PE VA 004FC650..004FC6DD; subtract 00400000 for RVA.
  4fc650:	56                   	push   esi
  4fc651:	8b c2                	mov    eax,edx
  4fc653:	8b f1                	mov    esi,ecx
  4fc655:	57                   	push   edi
  4fc656:	8b 3d 5c ba 5b 06    	mov    edi,DWORD PTR ds:0x65bba5c
  4fc65c:	33 d2                	xor    edx,edx
  4fc65e:	6a 00                	push   0x0
  4fc660:	8b c8                	mov    ecx,eax
  4fc662:	c7 05 5c ba 5b 06 01 	mov    DWORD PTR ds:0x65bba5c,0x1
  4fc669:	00 00 00 
  4fc66c:	e8 0f 63 01 00       	call   0x512980
  4fc671:	83 c4 04             	add    esp,0x4
  4fc674:	8b ce                	mov    ecx,esi
  4fc676:	e8 05 c9 ff ff       	call   0x4f8f80
  4fc67b:	6a 5a                	push   0x5a
  4fc67d:	ba 3a 02 00 00       	mov    edx,0x23a
  4fc682:	b9 a0 a7 5a 00       	mov    ecx,0x5aa7a0
  4fc687:	e8 f4 62 01 00       	call   0x512980
  4fc68c:	83 c4 04             	add    esp,0x4
  4fc68f:	89 3d 5c ba 5b 06    	mov    DWORD PTR ds:0x65bba5c,edi
  4fc695:	85 ff                	test   edi,edi
  4fc697:	75 41                	jne    0x4fc6da
  4fc699:	e8 f2 e8 00 00       	call   0x50af90
  4fc69e:	39 3d d8 bc 5b 06    	cmp    DWORD PTR ds:0x65bbcd8,edi
  4fc6a4:	74 17                	je     0x4fc6bd
  4fc6a6:	e8 95 39 01 00       	call   0x510040
  4fc6ab:	a1 d8 bc 5b 06       	mov    eax,ds:0x65bbcd8
  4fc6b0:	33 c9                	xor    ecx,ecx
  4fc6b2:	83 f8 02             	cmp    eax,0x2
  4fc6b5:	0f 44 c1             	cmove  eax,ecx
  4fc6b8:	a3 d8 bc 5b 06       	mov    ds:0x65bbcd8,eax
  4fc6bd:	e8 fe ec 00 00       	call   0x50b3c0
  4fc6c2:	83 3d 54 1c 5c 0a 00 	cmp    DWORD PTR ds:0xa5c1c54,0x0
  4fc6c9:	75 0f                	jne    0x4fc6da
  4fc6cb:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  4fc6d1:	ff 15 7c c2 58 00    	call   DWORD PTR ds:0x58c27c
  4fc6d7:	83 c4 04             	add    esp,0x4
  4fc6da:	5f                   	pop    edi
  4fc6db:	5e                   	pop    esi
  4fc6dc:	c3                   	ret

# Original PE VA 004F8F80..004F9027; subtract 00400000 for RVA.
  4f8f80:	55                   	push   ebp
  4f8f81:	8b ec                	mov    ebp,esp
  4f8f83:	83 e4 f8             	and    esp,0xfffffff8
  4f8f86:	53                   	push   ebx
  4f8f87:	57                   	push   edi
  4f8f88:	8b f9                	mov    edi,ecx
  4f8f8a:	ba d8 01 00 00       	mov    edx,0x1d8
  4f8f8f:	6a 00                	push   0x0
  4f8f91:	b9 44 a1 5a 00       	mov    ecx,0x5aa144
  4f8f96:	e8 e5 99 01 00       	call   0x512980
  4f8f9b:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4f8fa0:	83 c4 04             	add    esp,0x4
  4f8fa3:	6a 54                	push   0x54
  4f8fa5:	68 fc 00 00 00       	push   0xfc
  4f8faa:	68 fc 00 00 00       	push   0xfc
  4f8faf:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4f8fb2:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  4f8fb8:	8b 0d 10 bb 5b 06    	mov    ecx,DWORD PTR ds:0x65bbb10
  4f8fbe:	8b d8                	mov    ebx,eax
  4f8fc0:	68 98 00 00 00       	push   0x98
  4f8fc5:	6a 5a                	push   0x5a
  4f8fc7:	6a 3c                	push   0x3c
  4f8fc9:	ff 71 04             	push   DWORD PTR [ecx+0x4]
  4f8fcc:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  4f8fd2:	05 00 10 00 00       	add    eax,0x1000
  4f8fd7:	ba 05 00 00 00       	mov    edx,0x5
  4f8fdc:	50                   	push   eax
  4f8fdd:	68 16 c6 58 00       	push   0x58c616
  4f8fe2:	6a 10                	push   0x10
  4f8fe4:	68 16 03 00 00       	push   0x316
  4f8fe9:	8b ca                	mov    ecx,edx
  4f8feb:	e8 80 ce 01 00       	call   0x515e70
  4f8ff0:	8b c7                	mov    eax,edi
  4f8ff2:	83 c4 30             	add    esp,0x30
  4f8ff5:	8d 50 01             	lea    edx,[eax+0x1]
  4f8ff8:	8a 08                	mov    cl,BYTE PTR [eax]
  4f8ffa:	40                   	inc    eax
  4f8ffb:	84 c9                	test   cl,cl
  4f8ffd:	75 f9                	jne    0x4f8ff8
  4f8fff:	2b c2                	sub    eax,edx
  4f9001:	b9 95 01 00 00       	mov    ecx,0x195
  4f9006:	c1 e0 03             	shl    eax,0x3
  4f9009:	99                   	cdq
  4f900a:	2b c2                	sub    eax,edx
  4f900c:	ba 09 00 00 00       	mov    edx,0x9
  4f9011:	6a 01                	push   0x1
  4f9013:	d1 f8                	sar    eax,1
  4f9015:	53                   	push   ebx
  4f9016:	2b c8                	sub    ecx,eax
  4f9018:	57                   	push   edi
  4f9019:	e8 82 55 01 00       	call   0x50e5a0
  4f901e:	83 c4 0c             	add    esp,0xc
  4f9021:	5f                   	pop    edi
  4f9022:	5b                   	pop    ebx
  4f9023:	8b e5                	mov    esp,ebp
  4f9025:	5d                   	pop    ebp
  4f9026:	c3                   	ret

# Original PE VA 004FDB00..004FDC95; subtract 00400000 for RVA.
  4fdb00:	55                   	push   ebp
  4fdb01:	8b ec                	mov    ebp,esp
  4fdb03:	83 e4 f8             	and    esp,0xfffffff8
  4fdb06:	51                   	push   ecx
  4fdb07:	56                   	push   esi
  4fdb08:	51                   	push   ecx
  4fdb09:	ba 1c ab 5a 00       	mov    edx,0x5aab1c
  4fdb0e:	b9 2c ab 5a 00       	mov    ecx,0x5aab2c
  4fdb13:	e8 38 eb ff ff       	call   0x4fc650
  4fdb18:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4fdb1d:	83 c4 04             	add    esp,0x4
  4fdb20:	8b 35 f8 c1 58 00    	mov    esi,DWORD PTR ds:0x58c1f8
  4fdb26:	6a 54                	push   0x54
  4fdb28:	68 fc 00 00 00       	push   0xfc
  4fdb2d:	68 fc 00 00 00       	push   0xfc
  4fdb32:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fdb35:	ff d6                	call   esi
  4fdb37:	83 c4 0c             	add    esp,0xc
  4fdb3a:	ba 1e 00 00 00       	mov    edx,0x1e
  4fdb3f:	6a 0f                	push   0xf
  4fdb41:	68 cc 01 00 00       	push   0x1cc
  4fdb46:	8d 4a ec             	lea    ecx,[edx-0x14]
  4fdb49:	e8 32 39 01 00       	call   0x511480
  4fdb4e:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4fdb53:	83 c4 0c             	add    esp,0xc
  4fdb56:	68 de 00 00 00       	push   0xde
  4fdb5b:	68 c4 00 00 00       	push   0xc4
  4fdb60:	68 b0 00 00 00       	push   0xb0
  4fdb65:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fdb68:	ff d6                	call   esi
  4fdb6a:	ba 22 00 00 00       	mov    edx,0x22
  4fdb6f:	6a 01                	push   0x1
  4fdb71:	50                   	push   eax
  4fdb72:	68 4c ab 5a 00       	push   0x5aab4c
  4fdb77:	8d 4a ed             	lea    ecx,[edx-0x13]
  4fdb7a:	e8 21 0a 01 00       	call   0x50e5a0
  4fdb7f:	83 c4 1c             	add    esp,0x1c
  4fdb82:	ba a4 01 00 00       	mov    edx,0x1a4
  4fdb87:	b9 0a 00 00 00       	mov    ecx,0xa
  4fdb8c:	6a 04                	push   0x4
  4fdb8e:	68 16 c6 58 00       	push   0x58c616
  4fdb93:	6a 75                	push   0x75
  4fdb95:	68 cc 01 00 00       	push   0x1cc
  4fdb9a:	e8 d1 82 01 00       	call   0x515e70
  4fdb9f:	83 c4 10             	add    esp,0x10
  4fdba2:	b9 88 ab 5a 00       	mov    ecx,0x5aab88
  4fdba7:	e8 84 49 06 00       	call   0x562530
  4fdbac:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4fdbb1:	6a 01                	push   0x1
  4fdbb3:	68 aa 00 00 00       	push   0xaa
  4fdbb8:	68 e8 00 00 00       	push   0xe8
  4fdbbd:	68 ee 00 00 00       	push   0xee
  4fdbc2:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fdbc5:	ff d6                	call   esi
  4fdbc7:	83 c4 10             	add    esp,0x10
  4fdbca:	ba ae 01 00 00       	mov    edx,0x1ae
  4fdbcf:	b9 14 00 00 00       	mov    ecx,0x14
  4fdbd4:	50                   	push   eax
  4fdbd5:	6a 64                	push   0x64
  4fdbd7:	68 72 01 00 00       	push   0x172
  4fdbdc:	e8 5f 0f 01 00       	call   0x50eb40
  4fdbe1:	ba a9 01 00 00       	mov    edx,0x1a9
  4fdbe6:	83 c4 0c             	add    esp,0xc
  4fdbe9:	8d 4a fb             	lea    ecx,[edx-0x5]
  4fdbec:	e8 ff 90 fd ff       	call   0x4d6cf0
  4fdbf1:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4fdbf6:	83 c4 04             	add    esp,0x4
  4fdbf9:	6a 01                	push   0x1
  4fdbfb:	68 e0 00 00 00       	push   0xe0
  4fdc00:	68 ff 00 00 00       	push   0xff
  4fdc05:	68 ff 00 00 00       	push   0xff
  4fdc0a:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fdc0d:	ff d6                	call   esi
  4fdc0f:	83 c4 10             	add    esp,0x10
  4fdc12:	ba b8 01 00 00       	mov    edx,0x1b8
  4fdc17:	50                   	push   eax
  4fdc18:	68 90 ab 5a 00       	push   0x5aab90
  4fdc1d:	8d 4a c9             	lea    ecx,[edx-0x37]
  4fdc20:	e8 7b 09 01 00       	call   0x50e5a0
  4fdc25:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4fdc2a:	83 c4 0c             	add    esp,0xc
  4fdc2d:	6a 01                	push   0x1
  4fdc2f:	68 e0 00 00 00       	push   0xe0
  4fdc34:	68 ff 00 00 00       	push   0xff
  4fdc39:	68 ff 00 00 00       	push   0xff
  4fdc3e:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fdc41:	ff d6                	call   esi
  4fdc43:	83 c4 10             	add    esp,0x10
  4fdc46:	ba db 01 00 00       	mov    edx,0x1db
  4fdc4b:	50                   	push   eax
  4fdc4c:	68 9c ab 5a 00       	push   0x5aab9c
  4fdc51:	8d 4a a6             	lea    ecx,[edx-0x5a]
  4fdc54:	e8 47 09 01 00       	call   0x50e5a0
  4fdc59:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4fdc5e:	83 c4 0c             	add    esp,0xc
  4fdc61:	6a 01                	push   0x1
  4fdc63:	68 e0 00 00 00       	push   0xe0
  4fdc68:	68 ff 00 00 00       	push   0xff
  4fdc6d:	68 ff 00 00 00       	push   0xff
  4fdc72:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fdc75:	ff d6                	call   esi
  4fdc77:	83 c4 10             	add    esp,0x10
  4fdc7a:	ba fe 01 00 00       	mov    edx,0x1fe
  4fdc7f:	50                   	push   eax
  4fdc80:	68 a8 ab 5a 00       	push   0x5aaba8
  4fdc85:	8d 4a 83             	lea    ecx,[edx-0x7d]
  4fdc88:	e8 13 09 01 00       	call   0x50e5a0
  4fdc8d:	83 c4 0c             	add    esp,0xc
  4fdc90:	5e                   	pop    esi
  4fdc91:	8b e5                	mov    esp,ebp
  4fdc93:	5d                   	pop    ebp
  4fdc94:	c3                   	ret

# Original PE VA 00562530..00562690; subtract 00400000 for RVA.
  562530:	55                   	push   ebp
  562531:	8b ec                	mov    ebp,esp
  562533:	81 ec 74 08 00 00    	sub    esp,0x874
  562539:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  56253e:	33 c5                	xor    eax,ebp
  562540:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  562543:	53                   	push   ebx
  562544:	56                   	push   esi
  562545:	57                   	push   edi
  562546:	51                   	push   ecx
  562547:	8d 45 90             	lea    eax,[ebp-0x70]
  56254a:	33 db                	xor    ebx,ebx
  56254c:	68 f8 4f 59 00       	push   0x594ff8
  562551:	50                   	push   eax
  562552:	e8 79 eb e9 ff       	call   0x4010d0
  562557:	83 c4 0c             	add    esp,0xc
  56255a:	8d 85 90 f7 ff ff    	lea    eax,[ebp-0x870]
  562560:	68 b8 ac 5e 00       	push   0x5eacb8
  562565:	68 c4 81 5d 00       	push   0x5d81c4
  56256a:	50                   	push   eax
  56256b:	e8 60 eb e9 ff       	call   0x4010d0
  562570:	83 c4 0c             	add    esp,0xc
  562573:	8d 95 90 f7 ff ff    	lea    edx,[ebp-0x870]
  562579:	be 01 00 00 00       	mov    esi,0x1
  56257e:	8b ce                	mov    ecx,esi
  562580:	e8 7b fd ff ff       	call   0x562300
  562585:	8d 55 90             	lea    edx,[ebp-0x70]
  562588:	33 c9                	xor    ecx,ecx
  56258a:	e8 71 fd ff ff       	call   0x562300
  56258f:	8d 85 90 f7 ff ff    	lea    eax,[ebp-0x870]
  562595:	68 f8 f1 58 00       	push   0x58f1f8
  56259a:	50                   	push   eax
  56259b:	ff 15 78 c4 58 00    	call   DWORD PTR ds:0x58c478
  5625a1:	8b f8                	mov    edi,eax
  5625a3:	83 c4 08             	add    esp,0x8
  5625a6:	85 ff                	test   edi,edi
  5625a8:	0f 84 ec 00 00 00    	je     0x56269a
  5625ae:	57                   	push   edi
  5625af:	ff 15 e0 c4 58 00    	call   DWORD PTR ds:0x58c4e0
  5625b5:	83 c4 04             	add    esp,0x4
  5625b8:	85 c0                	test   eax,eax
  5625ba:	0f 85 d0 00 00 00    	jne    0x562690
  5625c0:	57                   	push   edi
  5625c1:	ba 2c 01 00 00       	mov    edx,0x12c
  5625c6:	8d 8d 90 fb ff ff    	lea    ecx,[ebp-0x470]
  5625cc:	e8 af 1c f7 ff       	call   0x4d4280
  5625d1:	8b c3                	mov    eax,ebx
  5625d3:	83 c4 04             	add    esp,0x4
  5625d6:	83 e8 00             	sub    eax,0x0
  5625d9:	74 58                	je     0x562633
  5625db:	83 e8 01             	sub    eax,0x1
  5625de:	0f 85 9a 00 00 00    	jne    0x56267e
  5625e4:	8d b5 90 fb ff ff    	lea    esi,[ebp-0x470]
  5625ea:	8d 4e 01             	lea    ecx,[esi+0x1]
  5625ed:	0f 1f 00             	nop    DWORD PTR [eax]
  5625f0:	8a 06                	mov    al,BYTE PTR [esi]
  5625f2:	46                   	inc    esi
  5625f3:	84 c0                	test   al,al
  5625f5:	75 f9                	jne    0x5625f0
  5625f7:	8d 85 90 fb ff ff    	lea    eax,[ebp-0x470]
  5625fd:	2b f1                	sub    esi,ecx
  5625ff:	68 8c 50 59 00       	push   0x59508c
  562604:	50                   	push   eax
  562605:	ff 15 50 c3 58 00    	call   DWORD PTR ds:0x58c350
  56260b:	83 c4 08             	add    esp,0x8
  56260e:	f7 d8                	neg    eax
  562610:	1b c0                	sbb    eax,eax
  562612:	33 c9                	xor    ecx,ecx
  562614:	f7 d8                	neg    eax
  562616:	85 f6                	test   esi,esi
  562618:	0f 94 c1             	sete   cl
  56261b:	0b c1                	or     eax,ecx
  56261d:	75 71                	jne    0x562690
  56261f:	8d 95 90 fb ff ff    	lea    edx,[ebp-0x470]
  562625:	33 c9                	xor    ecx,ecx
  562627:	e8 d4 fc ff ff       	call   0x562300
  56262c:	be 01 00 00 00       	mov    esi,0x1
  562631:	eb 4b                	jmp    0x56267e
  562633:	8d 45 90             	lea    eax,[ebp-0x70]
  562636:	50                   	push   eax
  562637:	8d 85 90 fb ff ff    	lea    eax,[ebp-0x470]
  56263d:	50                   	push   eax
  56263e:	ff 15 50 c3 58 00    	call   DWORD PTR ds:0x58c350
  562644:	83 c4 08             	add    esp,0x8
  562647:	85 c0                	test   eax,eax
  562649:	b8 18 53 62 0a       	mov    eax,0xa625318
  56264e:	0f 45 de             	cmovne ebx,esi
  562651:	c6 00 00             	mov    BYTE PTR [eax],0x0
  562654:	05 82 00 00 00       	add    eax,0x82
  562659:	3d 28 3e 6c 0a       	cmp    eax,0xa6c3e28
  56265e:	7c f1                	jl     0x562651
  562660:	68 00 04 00 00       	push   0x400
  562665:	6a 00                	push   0x0
  562667:	68 50 b6 5b 06       	push   0x65bb650
  56266c:	c7 05 14 53 62 0a 00 	mov    DWORD PTR ds:0xa625314,0x0
  562673:	00 00 00 
  562676:	e8 e5 87 02 00       	call   0x58ae60
  56267b:	83 c4 0c             	add    esp,0xc
  56267e:	57                   	push   edi
  56267f:	ff 15 e0 c4 58 00    	call   DWORD PTR ds:0x58c4e0
  562685:	83 c4 04             	add    esp,0x4
  562688:	85 c0                	test   eax,eax
  56268a:	0f 84 30 ff ff ff    	je     0x5625c0
