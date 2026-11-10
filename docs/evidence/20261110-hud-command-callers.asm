  4a3c6d:	68 54 ed 59 00       	push   0x59ed54
  4a3c72:	50                   	push   eax
  4a3c73:	e8 58 d4 f5 ff       	call   0x4010d0
  4a3c78:	83 c4 0c             	add    esp,0xc
  4a3c7b:	8d 95 f8 fb ff ff    	lea    edx,[ebp-0x408]
  4a3c81:	b9 ac ec 59 00       	mov    ecx,0x59ecac
  4a3c86:	e8 c5 d1 05 00       	call   0x500e50
  4a3c8b:	83 fe 52             	cmp    esi,0x52
  4a3c8e:	75 0a                	jne    0x4a3c9a
  4a3c90:	e8 db f8 ff ff       	call   0x4a3570
  4a3c95:	e9 a0 01 00 00       	jmp    0x4a3e3a
  4a3c9a:	83 fe 2d             	cmp    esi,0x2d
  4a3c9d:	75 4d                	jne    0x4a3cec
  4a3c9f:	b9 54 ec 59 00       	mov    ecx,0x59ec54
  4a3ca4:	e8 27 54 05 00       	call   0x4f90d0
  4a3ca9:	80 3d e6 bc 72 0a 02 	cmp    BYTE PTR ds:0xa72bce6,0x2
  4a3cb0:	75 16                	jne    0x4a3cc8

  4a3cbc:	c6 05 e3 cc 58 04 00 	mov    BYTE PTR ds:0x458cce3,0x0
  4a3cc3:	e9 72 01 00 00       	jmp    0x4a3e3a
  4a3cc8:	6a 24                	push   0x24
  4a3cca:	6a 00                	push   0x0
  4a3ccc:	68 c0 cb 59 00       	push   0x59cbc0
  4a3cd1:	33 d2                	xor    edx,edx
  4a3cd3:	c6 05 e7 bc 72 0a 01 	mov    BYTE PTR ds:0xa72bce7,0x1
  4a3cda:	b9 f0 00 00 00       	mov    ecx,0xf0
  4a3cdf:	e8 5c 4b fe ff       	call   0x488840
  4a3ce4:	83 c4 0c             	add    esp,0xc
  4a3ce7:	e9 4e 01 00 00       	jmp    0x4a3e3a
  4a3cec:	83 fe 46             	cmp    esi,0x46
  4a3cef:	75 37                	jne    0x4a3d28
  4a3cf1:	b9 60 ec 59 00       	mov    ecx,0x59ec60
  4a3cf6:	e8 d5 53 05 00       	call   0x4f90d0
  4a3cfb:	80 3d e6 bc 72 0a 02 	cmp    BYTE PTR ds:0xa72bce6,0x2
  4a3d02:	74 ae                	je     0x4a3cb2

  4a3d7f:	e9 b6 00 00 00       	jmp    0x4a3e3a
  4a3d84:	68 16 c6 58 00       	push   0x58c616
  4a3d89:	33 d2                	xor    edx,edx
  4a3d8b:	b9 c4 01 00 00       	mov    ecx,0x1c4
  4a3d90:	e8 bb fb 0b 00       	call   0x563950
  4a3d95:	83 c4 04             	add    esp,0x4
  4a3d98:	c6 05 e3 cc 58 04 01 	mov    BYTE PTR ds:0x458cce3,0x1
  4a3d9f:	e9 96 00 00 00       	jmp    0x4a3e3a
  4a3da4:	83 fe 53             	cmp    esi,0x53
  4a3da7:	75 3e                	jne    0x4a3de7
  4a3da9:	ba 5c ed 59 00       	mov    edx,0x59ed5c
  4a3dae:	b9 ac ec 59 00       	mov    ecx,0x59ecac
  4a3db3:	e8 98 d0 05 00       	call   0x500e50
  4a3db8:	b9 30 ed 59 00       	mov    ecx,0x59ed30
  4a3dbd:	e8 0e 53 05 00       	call   0x4f90d0
  4a3dc2:	68 16 c6 58 00       	push   0x58c616
  4a3dc7:	33 d2                	xor    edx,edx

  4fa312:	68 e2 00 00 00       	push   0xe2
  4fa317:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4fa31a:	ff d7                	call   edi
  4fa31c:	8b 15 e8 8c 5a 06    	mov    edx,DWORD PTR ds:0x65a8ce8
  4fa322:	8b 0d e4 8c 5a 06    	mov    ecx,DWORD PTR ds:0x65a8ce4
  4fa328:	50                   	push   eax
  4fa329:	68 00 10 00 00       	push   0x1000
  4fa32e:	68 16 c6 58 00       	push   0x58c616
  4fa333:	ff 35 f0 8c 5a 06    	push   DWORD PTR ds:0x65a8cf0
  4fa339:	ff 35 ec 8c 5a 06    	push   DWORD PTR ds:0x65a8cec
  4fa33f:	e8 2c bf 01 00       	call   0x516270
  4fa344:	83 c4 24             	add    esp,0x24
  4fa347:	c6 05 e9 e0 b8 04 00 	mov    BYTE PTR ds:0x4b8e0e9,0x0
  4fa34e:	b9 54 a1 5a 00       	mov    ecx,0x5aa154
  4fa353:	e8 78 ed ff ff       	call   0x4f90d0
  4fa358:	33 c9                	xor    ecx,ecx
  4fa35a:	e8 a1 f2 ff ff       	call   0x4f9600

  523332:	89 45 98             	mov    DWORD PTR [ebp-0x68],eax
  523335:	a0 18 06 59 00       	mov    al,ds:0x590618
  52333a:	66 0f d6 45 90       	movq   QWORD PTR [ebp-0x70],xmm0
  52333f:	88 45 9c             	mov    BYTE PTR [ebp-0x64],al
  523342:	eb 19                	jmp    0x52335d
  523344:	8d 4d 90             	lea    ecx,[ebp-0x70]
  523347:	2b ce                	sub    ecx,esi
  523349:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [eax+0x0]
  523350:	8a 06                	mov    al,BYTE PTR [esi]
  523352:	8d 76 01             	lea    esi,[esi+0x1]
  523355:	88 44 31 ff          	mov    BYTE PTR [ecx+esi*1-0x1],al
  523359:	84 c0                	test   al,al
  52335b:	75 f3                	jne    0x523350
  52335d:	8d 4d 90             	lea    ecx,[ebp-0x70]
  523360:	e8 6b 5d fd ff       	call   0x4f90d0
  523365:	33 d2                	xor    edx,edx
  523367:	83 c9 ff             	or     ecx,0xffffffff

  53274a:	8b 3d b0 22 61 0a    	mov    edi,DWORD PTR ds:0xa6122b0
  532750:	80 f9 33             	cmp    cl,0x33
  532753:	75 0c                	jne    0x532761
  532755:	c7 05 d8 22 61 0a 01 	mov    DWORD PTR ds:0xa6122d8,0x1
  53275c:	00 00 00 
  53275f:	8a cb                	mov    cl,bl
  532761:	0f b6 c1             	movzx  eax,cl
  532764:	a3 d4 22 61 0a       	mov    ds:0xa6122d4,eax
  532769:	8d 70 d0             	lea    esi,[eax-0x30]
  53276c:	83 fe 44             	cmp    esi,0x44
  53276f:	77 64                	ja     0x5327d5
  532771:	0f b6 86 14 28 53 00 	movzx  eax,BYTE PTR [esi+0x532814]
  532778:	ff 24 85 00 28 53 00 	jmp    DWORD PTR [eax*4+0x532800]
  53277f:	b9 d4 14 5b 00       	mov    ecx,0x5b14d4
  532784:	e8 47 69 fc ff       	call   0x4f90d0
  532789:	e8 62 b5 f1 ff       	call   0x44dcf0
  53278e:	eb 42                	jmp    0x5327d2

  532764:	a3 d4 22 61 0a       	mov    ds:0xa6122d4,eax
  532769:	8d 70 d0             	lea    esi,[eax-0x30]
  53276c:	83 fe 44             	cmp    esi,0x44
  53276f:	77 64                	ja     0x5327d5
  532771:	0f b6 86 14 28 53 00 	movzx  eax,BYTE PTR [esi+0x532814]
  532778:	ff 24 85 00 28 53 00 	jmp    DWORD PTR [eax*4+0x532800]
  53277f:	b9 d4 14 5b 00       	mov    ecx,0x5b14d4
  532784:	e8 47 69 fc ff       	call   0x4f90d0
  532789:	e8 62 b5 f1 ff       	call   0x44dcf0
  53278e:	eb 42                	jmp    0x5327d2
  532790:	80 f9 31             	cmp    cl,0x31
  532793:	b9 e0 14 5b 00       	mov    ecx,0x5b14e0
  532798:	74 05                	je     0x53279f
  53279a:	b9 f4 14 5b 00       	mov    ecx,0x5b14f4
  53279f:	e8 2c 69 fc ff       	call   0x4f90d0
  5327a4:	8b ce                	mov    ecx,esi
  5327a6:	eb 20                	jmp    0x5327c8

  532771:	0f b6 86 14 28 53 00 	movzx  eax,BYTE PTR [esi+0x532814]
  532778:	ff 24 85 00 28 53 00 	jmp    DWORD PTR [eax*4+0x532800]
  53277f:	b9 d4 14 5b 00       	mov    ecx,0x5b14d4
  532784:	e8 47 69 fc ff       	call   0x4f90d0
  532789:	e8 62 b5 f1 ff       	call   0x44dcf0
  53278e:	eb 42                	jmp    0x5327d2
  532790:	80 f9 31             	cmp    cl,0x31
  532793:	b9 e0 14 5b 00       	mov    ecx,0x5b14e0
  532798:	74 05                	je     0x53279f
  53279a:	b9 f4 14 5b 00       	mov    ecx,0x5b14f4
  53279f:	e8 2c 69 fc ff       	call   0x4f90d0
  5327a4:	8b ce                	mov    ecx,esi
  5327a6:	eb 20                	jmp    0x5327c8
  5327a8:	b9 08 15 5b 00       	mov    ecx,0x5b1508
  5327ad:	e8 1e 69 fc ff       	call   0x4f90d0
  5327b2:	b9 03 00 00 00       	mov    ecx,0x3
  5327b7:	eb 0f                	jmp    0x5327c8

  532789:	e8 62 b5 f1 ff       	call   0x44dcf0
  53278e:	eb 42                	jmp    0x5327d2
  532790:	80 f9 31             	cmp    cl,0x31
  532793:	b9 e0 14 5b 00       	mov    ecx,0x5b14e0
  532798:	74 05                	je     0x53279f
  53279a:	b9 f4 14 5b 00       	mov    ecx,0x5b14f4
  53279f:	e8 2c 69 fc ff       	call   0x4f90d0
  5327a4:	8b ce                	mov    ecx,esi
  5327a6:	eb 20                	jmp    0x5327c8
  5327a8:	b9 08 15 5b 00       	mov    ecx,0x5b1508
  5327ad:	e8 1e 69 fc ff       	call   0x4f90d0
  5327b2:	b9 03 00 00 00       	mov    ecx,0x3
  5327b7:	eb 0f                	jmp    0x5327c8
  5327b9:	b9 10 15 5b 00       	mov    ecx,0x5b1510
  5327be:	e8 0d 69 fc ff       	call   0x4f90d0
  5327c3:	b9 04 00 00 00       	mov    ecx,0x4
  5327c8:	e8 93 f8 ff ff       	call   0x532060

  563953:	83 ec 78             	sub    esp,0x78
  563956:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  56395b:	33 c5                	xor    eax,ebp
  56395d:	89 45 f8             	mov    DWORD PTR [ebp-0x8],eax
  563960:	53                   	push   ebx
  563961:	56                   	push   esi
  563962:	8b f1                	mov    esi,ecx
  563964:	8b da                	mov    ebx,edx
  563966:	57                   	push   edi
  563967:	8b 7d 08             	mov    edi,DWORD PTR [ebp+0x8]
  56396a:	85 f6                	test   esi,esi
  56396c:	0f 84 d2 09 00 00    	je     0x564344
  563972:	e8 19 f8 ff ff       	call   0x563190
  563977:	8b c8                	mov    ecx,eax
  563979:	e8 52 57 f9 ff       	call   0x4f90d0
  56397e:	81 fe bd 02 00 00    	cmp    esi,0x2bd
  563984:	7f 1a                	jg     0x5639a0

  57cfe0:	e8 eb 40 e8 ff       	call   0x4010d0
  57cfe5:	8d 45 90             	lea    eax,[ebp-0x70]
  57cfe8:	33 d2                	xor    edx,edx
  57cfea:	50                   	push   eax
  57cfeb:	33 c9                	xor    ecx,ecx
  57cfed:	e8 8e 76 f9 ff       	call   0x514680
  57cff2:	83 c4 14             	add    esp,0x14
  57cff5:	e8 26 e7 f8 ff       	call   0x50b720
  57cffa:	83 3d fc 08 79 05 00 	cmp    DWORD PTR ds:0x57908fc,0x0
  57d001:	74 05                	je     0x57d008
  57d003:	e8 58 2b f4 ff       	call   0x4bfb60
  57d008:	8b cb                	mov    ecx,ebx
  57d00a:	e8 f1 c5 f7 ff       	call   0x4f9600
  57d00f:	b9 16 c6 58 00       	mov    ecx,0x58c616
  57d014:	e8 b7 c0 f7 ff       	call   0x4f90d0
  57d019:	83 3d 7c 9c 5e 00 00 	cmp    DWORD PTR ds:0x5e9c7c,0x0
  57d020:	c7 05 fc ba 5b 06 00 	mov    DWORD PTR ds:0x65bbafc,0x0

  57d0e6:	74 16                	je     0x57d0fe
  57d0e8:	b9 dc c2 5d 00       	mov    ecx,0x5dc2dc
  57d0ed:	e8 1e 94 f7 ff       	call   0x4f6510
  57d0f2:	b9 10 c3 5d 00       	mov    ecx,0x5dc310
  57d0f7:	e8 14 94 f7 ff       	call   0x4f6510
  57d0fc:	33 db                	xor    ebx,ebx
  57d0fe:	68 40 c3 5d 00       	push   0x5dc340
  57d103:	c7 05 f8 40 78 0a 00 	mov    DWORD PTR ds:0xa7840f8,0x0
  57d10a:	00 00 00 
  57d10d:	ff 15 88 c3 58 00    	call   DWORD PTR ds:0x58c388
  57d113:	83 c4 04             	add    esp,0x4
  57d116:	83 fb 0d             	cmp    ebx,0xd
  57d119:	0f 85 04 02 00 00    	jne    0x57d323
  57d11f:	b9 4c c3 5d 00       	mov    ecx,0x5dc34c
  57d124:	e8 a7 bf f7 ff       	call   0x4f90d0
  57d129:	0f b6 05 e6 bc 72 0a 	movzx  eax,BYTE PTR ds:0xa72bce6
  57d130:	83 e8 02             	sub    eax,0x2

  57d360:	83 f8 32             	cmp    eax,0x32
  57d363:	7c e2                	jl     0x57d347
  57d365:	eb 23                	jmp    0x57d38a
  57d367:	8b 0c 85 80 38 39 06 	mov    ecx,DWORD PTR [eax*4+0x6393880]
  57d36e:	eb 10                	jmp    0x57d380
  57d370:	8b 0c 85 58 c7 36 06 	mov    ecx,DWORD PTR [eax*4+0x636c758]
  57d377:	eb 07                	jmp    0x57d380
  57d379:	8b 0c 85 80 cc 35 06 	mov    ecx,DWORD PTR [eax*4+0x635cc80]
  57d380:	83 f9 ff             	cmp    ecx,0xffffffff
  57d383:	74 05                	je     0x57d38a
  57d385:	e8 46 5f fa ff       	call   0x5232d0
  57d38a:	81 fb 48 04 00 00    	cmp    ebx,0x448
  57d390:	75 4d                	jne    0x57d3df
  57d392:	b9 60 ec 59 00       	mov    ecx,0x59ec60
  57d397:	e8 34 bd f7 ff       	call   0x4f90d0
  57d39c:	80 3d e6 bc 72 0a 02 	cmp    BYTE PTR ds:0xa72bce6,0x2
  57d3a3:	75 16                	jne    0x57d3bb

  57d46e:	0f 44 d8             	cmove  ebx,eax
  57d471:	83 3d 98 40 78 0a 00 	cmp    DWORD PTR ds:0xa784098,0x0
  57d478:	75 55                	jne    0x57d4cf
  57d47a:	81 fb 4c 04 00 00    	cmp    ebx,0x44c
  57d480:	75 4d                	jne    0x57d4cf
  57d482:	a1 24 c7 5a 00       	mov    eax,ds:0x5ac724
  57d487:	b9 b8 a8 5e 00       	mov    ecx,0x5ea8b8
  57d48c:	f3 0f 7e 05 1c c7 5a 	movq   xmm0,QWORD PTR ds:0x5ac71c
  57d493:	00 
  57d494:	a3 c0 a8 5e 00       	mov    ds:0x5ea8c0,eax
  57d499:	66 a1 28 c7 5a 00    	mov    ax,ds:0x5ac728
  57d49f:	66 0f d6 05 b8 a8 5e 	movq   QWORD PTR ds:0x5ea8b8,xmm0
  57d4a6:	00 
  57d4a7:	66 a3 c4 a8 5e 00    	mov    ds:0x5ea8c4,ax
  57d4ad:	e8 1e bc f7 ff       	call   0x4f90d0
  57d4b2:	b9 01 00 00 00       	mov    ecx,0x1
  57d4b7:	e8 c4 a0 f6 ff       	call   0x4e7580

  57d4d8:	81 fb 25 04 00 00    	cmp    ebx,0x425
  57d4de:	0f 84 ac 00 00 00    	je     0x57d590
  57d4e4:	83 fb 67             	cmp    ebx,0x67
  57d4e7:	74 53                	je     0x57d53c
  57d4e9:	83 fb 2c             	cmp    ebx,0x2c
  57d4ec:	74 4e                	je     0x57d53c
  57d4ee:	83 fb 47             	cmp    ebx,0x47
  57d4f1:	74 09                	je     0x57d4fc
  57d4f3:	83 fb 3b             	cmp    ebx,0x3b
  57d4f6:	0f 85 bf 00 00 00    	jne    0x57d5bb
  57d4fc:	ff 15 84 c2 58 00    	call   DWORD PTR ds:0x58c284
  57d502:	a8 c0                	test   al,0xc0
  57d504:	74 19                	je     0x57d51f
  57d506:	b9 1c c4 5d 00       	mov    ecx,0x5dc41c
  57d50b:	e8 c0 bb f7 ff       	call   0x4f90d0
  57d510:	b9 01 00 00 00       	mov    ecx,0x1
  57d515:	e8 66 fa ec ff       	call   0x44cf80

  57d4f3:	83 fb 3b             	cmp    ebx,0x3b
  57d4f6:	0f 85 bf 00 00 00    	jne    0x57d5bb
  57d4fc:	ff 15 84 c2 58 00    	call   DWORD PTR ds:0x58c284
  57d502:	a8 c0                	test   al,0xc0
  57d504:	74 19                	je     0x57d51f
  57d506:	b9 1c c4 5d 00       	mov    ecx,0x5dc41c
  57d50b:	e8 c0 bb f7 ff       	call   0x4f90d0
  57d510:	b9 01 00 00 00       	mov    ecx,0x1
  57d515:	e8 66 fa ec ff       	call   0x44cf80
  57d51a:	e9 9a 00 00 00       	jmp    0x57d5b9
  57d51f:	33 d2                	xor    edx,edx
  57d521:	8d 4a 47             	lea    ecx,[edx+0x47]
  57d524:	e8 f7 71 fe ff       	call   0x564720
  57d529:	8b c8                	mov    ecx,eax
  57d52b:	e8 a0 bb f7 ff       	call   0x4f90d0
  57d530:	33 c9                	xor    ecx,ecx
  57d532:	e8 49 fa ec ff       	call   0x44cf80

  57d515:	e8 66 fa ec ff       	call   0x44cf80
  57d51a:	e9 9a 00 00 00       	jmp    0x57d5b9
  57d51f:	33 d2                	xor    edx,edx
  57d521:	8d 4a 47             	lea    ecx,[edx+0x47]
  57d524:	e8 f7 71 fe ff       	call   0x564720
  57d529:	8b c8                	mov    ecx,eax
  57d52b:	e8 a0 bb f7 ff       	call   0x4f90d0
  57d530:	33 c9                	xor    ecx,ecx
  57d532:	e8 49 fa ec ff       	call   0x44cf80
  57d537:	e9 7d 00 00 00       	jmp    0x57d5b9
  57d53c:	ff 15 84 c2 58 00    	call   DWORD PTR ds:0x58c284
  57d542:	a8 c0                	test   al,0xc0
  57d544:	74 0e                	je     0x57d554
  57d546:	b9 1c c4 5d 00       	mov    ecx,0x5dc41c
  57d54b:	e8 80 bb f7 ff       	call   0x4f90d0
  57d550:	6a 01                	push   0x1
  57d552:	eb 26                	jmp    0x57d57a

  57d532:	e8 49 fa ec ff       	call   0x44cf80
  57d537:	e9 7d 00 00 00       	jmp    0x57d5b9
  57d53c:	ff 15 84 c2 58 00    	call   DWORD PTR ds:0x58c284
  57d542:	a8 c0                	test   al,0xc0
  57d544:	74 0e                	je     0x57d554
  57d546:	b9 1c c4 5d 00       	mov    ecx,0x5dc41c
  57d54b:	e8 80 bb f7 ff       	call   0x4f90d0
  57d550:	6a 01                	push   0x1
  57d552:	eb 26                	jmp    0x57d57a
  57d554:	0f 10 05 e4 89 5d 00 	movups xmm0,XMMWORD PTR ds:0x5d89e4
  57d55b:	66 a1 f4 89 5d 00    	mov    ax,ds:0x5d89f4
  57d561:	b9 b8 a8 5e 00       	mov    ecx,0x5ea8b8
  57d566:	66 a3 c8 a8 5e 00    	mov    ds:0x5ea8c8,ax
  57d56c:	0f 11 05 b8 a8 5e 00 	movups XMMWORD PTR ds:0x5ea8b8,xmm0
  57d573:	e8 58 bb f7 ff       	call   0x4f90d0
  57d578:	6a 00                	push   0x0
  57d57a:	8b 15 40 bd 72 0a    	mov    edx,DWORD PTR ds:0xa72bd40

  57d573:	e8 58 bb f7 ff       	call   0x4f90d0
  57d578:	6a 00                	push   0x0
  57d57a:	8b 15 40 bd 72 0a    	mov    edx,DWORD PTR ds:0xa72bd40
  57d580:	8b 0d 9c 1c 6d 0a    	mov    ecx,DWORD PTR ds:0xa6d1c9c
  57d586:	e8 f5 f6 ec ff       	call   0x44cc80
  57d58b:	83 c4 04             	add    esp,0x4
  57d58e:	eb 29                	jmp    0x57d5b9
  57d590:	f3 0f 7e 05 b4 89 5d 	movq   xmm0,QWORD PTR ds:0x5d89b4
  57d597:	00 
  57d598:	b9 b8 a8 5e 00       	mov    ecx,0x5ea8b8
  57d59d:	a1 bc 89 5d 00       	mov    eax,ds:0x5d89bc
  57d5a2:	66 0f d6 05 b8 a8 5e 	movq   QWORD PTR ds:0x5ea8b8,xmm0
  57d5a9:	00 
  57d5aa:	a3 c0 a8 5e 00       	mov    ds:0x5ea8c0,eax
  57d5af:	e8 1c bb f7 ff       	call   0x4f90d0
  57d5b4:	e8 e7 b0 f8 ff       	call   0x5086a0
  57d5b9:	33 db                	xor    ebx,ebx

  57d675:	83 c4 04             	add    esp,0x4
  57d678:	c6 05 e3 cc 58 04 01 	mov    BYTE PTR ds:0x458cce3,0x1
  57d67f:	e9 92 00 00 00       	jmp    0x57d716
  57d684:	83 fb 5a             	cmp    ebx,0x5a
  57d687:	75 3c                	jne    0x57d6c5
  57d689:	b9 38 c4 5d 00       	mov    ecx,0x5dc438
  57d68e:	e8 9d 69 fa ff       	call   0x524030
  57d693:	84 c0                	test   al,al
  57d695:	74 0e                	je     0x57d6a5
  57d697:	b9 4c c4 5d 00       	mov    ecx,0x5dc44c
  57d69c:	e8 ff e1 f7 ff       	call   0x4fb8a0
  57d6a1:	84 c0                	test   al,al
  57d6a3:	74 6f                	je     0x57d714
  57d6a5:	b9 30 ed 59 00       	mov    ecx,0x59ed30
  57d6aa:	e8 21 ba f7 ff       	call   0x4f90d0
  57d6af:	68 16 c6 58 00       	push   0x58c616
  57d6b4:	33 d2                	xor    edx,edx

  57d6ca:	83 fb 2b             	cmp    ebx,0x2b
  57d6cd:	74 36                	je     0x57d705
  57d6cf:	83 fb 3d             	cmp    ebx,0x3d
  57d6d2:	74 31                	je     0x57d705
  57d6d4:	81 fb 3a 04 00 00    	cmp    ebx,0x43a
  57d6da:	0f 8f 98 05 00 00    	jg     0x57dc78
  57d6e0:	75 34                	jne    0x57d716
  57d6e2:	80 3d e6 bc 72 0a 02 	cmp    BYTE PTR ds:0xa72bce6,0x2
  57d6e9:	0f 85 67 05 00 00    	jne    0x57dc56
  57d6ef:	8b 15 40 bd 72 0a    	mov    edx,DWORD PTR ds:0xa72bd40
  57d6f5:	8b 0d 9c 1c 6d 0a    	mov    ecx,DWORD PTR ds:0xa6d1c9c
  57d6fb:	e8 b0 27 f2 ff       	call   0x49feb0
  57d700:	e9 58 05 00 00       	jmp    0x57dc5d
  57d705:	b9 58 c4 5d 00       	mov    ecx,0x5dc458
  57d70a:	e8 c1 b9 f7 ff       	call   0x4f90d0
  57d70f:	e8 ec a3 ec ff       	call   0x447b00
  57d714:	33 db                	xor    ebx,ebx

  57d735:	e9 3e 05 00 00       	jmp    0x57dc78
  57d73a:	68 16 c6 58 00       	push   0x58c616
  57d73f:	33 d2                	xor    edx,edx
  57d741:	b9 c1 01 00 00       	mov    ecx,0x1c1
  57d746:	e8 05 62 fe ff       	call   0x563950
  57d74b:	83 c4 04             	add    esp,0x4
  57d74e:	e9 25 05 00 00       	jmp    0x57dc78
  57d753:	68 16 c6 58 00       	push   0x58c616
  57d758:	33 d2                	xor    edx,edx
  57d75a:	b9 c2 01 00 00       	mov    ecx,0x1c2
  57d75f:	e8 ec 61 fe ff       	call   0x563950
  57d764:	83 c4 04             	add    esp,0x4
  57d767:	e9 0c 05 00 00       	jmp    0x57dc78
  57d76c:	b9 60 c4 5d 00       	mov    ecx,0x5dc460
  57d771:	e8 5a b9 f7 ff       	call   0x4f90d0
  57d776:	e8 e5 b1 ec ff       	call   0x448960
  57d77b:	e9 16 09 00 00       	jmp    0x57e096

  57d753:	68 16 c6 58 00       	push   0x58c616
  57d758:	33 d2                	xor    edx,edx
  57d75a:	b9 c2 01 00 00       	mov    ecx,0x1c2
  57d75f:	e8 ec 61 fe ff       	call   0x563950
  57d764:	83 c4 04             	add    esp,0x4
  57d767:	e9 0c 05 00 00       	jmp    0x57dc78
  57d76c:	b9 60 c4 5d 00       	mov    ecx,0x5dc460
  57d771:	e8 5a b9 f7 ff       	call   0x4f90d0
  57d776:	e8 e5 b1 ec ff       	call   0x448960
  57d77b:	e9 16 09 00 00       	jmp    0x57e096
  57d780:	33 d2                	xor    edx,edx
  57d782:	8d 4a 66             	lea    ecx,[edx+0x66]
  57d785:	e8 96 6f fe ff       	call   0x564720
  57d78a:	8b c8                	mov    ecx,eax
  57d78c:	e8 3f b9 f7 ff       	call   0x4f90d0
  57d791:	33 d2                	xor    edx,edx
  57d793:	68 16 c6 58 00       	push   0x58c616

  57d782:	8d 4a 66             	lea    ecx,[edx+0x66]
  57d785:	e8 96 6f fe ff       	call   0x564720
  57d78a:	8b c8                	mov    ecx,eax
  57d78c:	e8 3f b9 f7 ff       	call   0x4f90d0
  57d791:	33 d2                	xor    edx,edx
  57d793:	68 16 c6 58 00       	push   0x58c616
  57d798:	8d 4a 21             	lea    ecx,[edx+0x21]
  57d79b:	e8 b0 61 fe ff       	call   0x563950
  57d7a0:	83 c4 04             	add    esp,0x4
  57d7a3:	e9 d0 04 00 00       	jmp    0x57dc78
  57d7a8:	33 d2                	xor    edx,edx
  57d7aa:	8d 4a 68             	lea    ecx,[edx+0x68]
  57d7ad:	e8 6e 6f fe ff       	call   0x564720
  57d7b2:	8b c8                	mov    ecx,eax
  57d7b4:	e8 17 b9 f7 ff       	call   0x4f90d0
  57d7b9:	e8 02 61 fe ff       	call   0x5638c0
  57d7be:	85 c0                	test   eax,eax

  57d7a8:	33 d2                	xor    edx,edx
  57d7aa:	8d 4a 68             	lea    ecx,[edx+0x68]
  57d7ad:	e8 6e 6f fe ff       	call   0x564720
  57d7b2:	8b c8                	mov    ecx,eax
  57d7b4:	e8 17 b9 f7 ff       	call   0x4f90d0
  57d7b9:	e8 02 61 fe ff       	call   0x5638c0
  57d7be:	85 c0                	test   eax,eax
  57d7c0:	0f 85 b2 04 00 00    	jne    0x57dc78
  57d7c6:	e8 b5 20 f2 ff       	call   0x49f880
  57d7cb:	e9 a8 04 00 00       	jmp    0x57dc78
  57d7d0:	33 d2                	xor    edx,edx
  57d7d2:	8d 4a 51             	lea    ecx,[edx+0x51]
  57d7d5:	e8 46 6f fe ff       	call   0x564720
  57d7da:	8b c8                	mov    ecx,eax
  57d7dc:	e8 ef b8 f7 ff       	call   0x4f90d0
  57d7e1:	33 c9                	xor    ecx,ecx
  57d7e3:	e8 98 9d f6 ff       	call   0x4e7580

  57d7fc:	5d                   	pop    ebp
  57d7fd:	c3                   	ret
  57d7fe:	80 3d eb c0 40 06 00 	cmp    BYTE PTR ds:0x640c0eb,0x0
  57d805:	0f 84 6d 04 00 00    	je     0x57dc78
  57d80b:	e8 30 39 00 00       	call   0x581140
  57d810:	e9 63 04 00 00       	jmp    0x57dc78
  57d815:	85 ff                	test   edi,edi
  57d817:	0f 85 5b 04 00 00    	jne    0x57dc78
  57d81d:	e8 5e 79 f0 ff       	call   0x485180
  57d822:	e9 51 04 00 00       	jmp    0x57dc78
  57d827:	33 d2                	xor    edx,edx
  57d829:	8d 4a 71             	lea    ecx,[edx+0x71]
  57d82c:	e8 ef 6e fe ff       	call   0x564720
  57d831:	8b c8                	mov    ecx,eax
  57d833:	e8 98 b8 f7 ff       	call   0x4f90d0
  57d838:	e8 23 89 eb ff       	call   0x436160
  57d83d:	e9 36 04 00 00       	jmp    0x57dc78

  57d80b:	e8 30 39 00 00       	call   0x581140
  57d810:	e9 63 04 00 00       	jmp    0x57dc78
  57d815:	85 ff                	test   edi,edi
  57d817:	0f 85 5b 04 00 00    	jne    0x57dc78
  57d81d:	e8 5e 79 f0 ff       	call   0x485180
  57d822:	e9 51 04 00 00       	jmp    0x57dc78
  57d827:	33 d2                	xor    edx,edx
  57d829:	8d 4a 71             	lea    ecx,[edx+0x71]
  57d82c:	e8 ef 6e fe ff       	call   0x564720
  57d831:	8b c8                	mov    ecx,eax
  57d833:	e8 98 b8 f7 ff       	call   0x4f90d0
  57d838:	e8 23 89 eb ff       	call   0x436160
  57d83d:	e9 36 04 00 00       	jmp    0x57dc78
  57d842:	b9 74 c4 5d 00       	mov    ecx,0x5dc474
  57d847:	e8 84 b8 f7 ff       	call   0x4f90d0
  57d84c:	e8 bf 01 f9 ff       	call   0x50da10
  57d851:	e8 0a d7 f8 ff       	call   0x50af60

  57d851:	e8 0a d7 f8 ff       	call   0x50af60
  57d856:	33 d2                	xor    edx,edx
  57d858:	33 c9                	xor    ecx,ecx
  57d85a:	e8 71 f0 f7 ff       	call   0x4fc8d0
  57d85f:	e8 dc d6 f8 ff       	call   0x50af40
  57d864:	e8 f7 01 f9 ff       	call   0x50da60
  57d869:	e9 0a 04 00 00       	jmp    0x57dc78
  57d86e:	68 16 c6 58 00       	push   0x58c616
  57d873:	33 d2                	xor    edx,edx
  57d875:	b9 84 03 00 00       	mov    ecx,0x384
  57d87a:	e8 d1 60 fe ff       	call   0x563950
  57d87f:	83 c4 04             	add    esp,0x4
  57d882:	e9 f1 03 00 00       	jmp    0x57dc78
  57d887:	b9 54 ec 59 00       	mov    ecx,0x59ec54
  57d88c:	e8 3f b8 f7 ff       	call   0x4f90d0
  57d891:	80 3d e6 bc 72 0a 02 	cmp    BYTE PTR ds:0xa72bce6,0x2
  57d898:	75 16                	jne    0x57d8b0

  57d89a:	b9 0c cb 59 00       	mov    ecx,0x59cb0c
  57d89f:	e8 6c 8c f7 ff       	call   0x4f6510
  57d8a4:	c6 05 e3 cc 58 04 00 	mov    BYTE PTR ds:0x458cce3,0x0
  57d8ab:	e9 c8 03 00 00       	jmp    0x57dc78
  57d8b0:	6a 24                	push   0x24
  57d8b2:	6a 00                	push   0x0
  57d8b4:	68 c0 cb 59 00       	push   0x59cbc0
  57d8b9:	33 d2                	xor    edx,edx
  57d8bb:	c6 05 e7 bc 72 0a 01 	mov    BYTE PTR ds:0xa72bce7,0x1
  57d8c2:	b9 f0 00 00 00       	mov    ecx,0xf0
  57d8c7:	e8 74 af f0 ff       	call   0x488840
  57d8cc:	83 c4 0c             	add    esp,0xc
  57d8cf:	e9 a4 03 00 00       	jmp    0x57dc78
  57d8d4:	b9 84 c4 5d 00       	mov    ecx,0x5dc484
  57d8d9:	e8 f2 b7 f7 ff       	call   0x4f90d0
  57d8de:	8b 15 3c 6a 6c 0a    	mov    edx,DWORD PTR ds:0xa6c6a3c
  57d8e4:	8b 0d a4 6a 6c 0a    	mov    ecx,DWORD PTR ds:0xa6c6aa4

  57d908:	e8 43 60 fe ff       	call   0x563950
  57d90d:	83 c4 04             	add    esp,0x4
  57d910:	e9 63 03 00 00       	jmp    0x57dc78
  57d915:	e8 46 d6 f8 ff       	call   0x50af60
  57d91a:	e8 51 60 f8 ff       	call   0x503970
  57d91f:	e8 1c d6 f8 ff       	call   0x50af40
  57d924:	e9 4f 03 00 00       	jmp    0x57dc78
  57d929:	b9 98 c4 5d 00       	mov    ecx,0x5dc498
  57d92e:	e8 dd 8b f7 ff       	call   0x4f6510
  57d933:	e9 40 03 00 00       	jmp    0x57dc78
  57d938:	33 d2                	xor    edx,edx
  57d93a:	8d 4a 65             	lea    ecx,[edx+0x65]
  57d93d:	e8 de 6d fe ff       	call   0x564720
  57d942:	8b c8                	mov    ecx,eax
  57d944:	e8 87 b7 f7 ff       	call   0x4f90d0
  57d949:	e8 22 81 eb ff       	call   0x435a70
  57d94e:	e9 25 03 00 00       	jmp    0x57dc78

  57d924:	e9 4f 03 00 00       	jmp    0x57dc78
  57d929:	b9 98 c4 5d 00       	mov    ecx,0x5dc498
  57d92e:	e8 dd 8b f7 ff       	call   0x4f6510
  57d933:	e9 40 03 00 00       	jmp    0x57dc78
  57d938:	33 d2                	xor    edx,edx
  57d93a:	8d 4a 65             	lea    ecx,[edx+0x65]
  57d93d:	e8 de 6d fe ff       	call   0x564720
  57d942:	8b c8                	mov    ecx,eax
  57d944:	e8 87 b7 f7 ff       	call   0x4f90d0
  57d949:	e8 22 81 eb ff       	call   0x435a70
  57d94e:	e9 25 03 00 00       	jmp    0x57dc78
  57d953:	e8 d8 60 f8 ff       	call   0x503a30
  57d958:	e9 1b 03 00 00       	jmp    0x57dc78
  57d95d:	b9 d0 c4 5d 00       	mov    ecx,0x5dc4d0
  57d962:	e8 69 b7 f7 ff       	call   0x4f90d0
  57d967:	e8 b4 ea fe ff       	call   0x56c420
  57d96c:	e9 07 03 00 00       	jmp    0x57dc78

  57d938:	33 d2                	xor    edx,edx
  57d93a:	8d 4a 65             	lea    ecx,[edx+0x65]
  57d93d:	e8 de 6d fe ff       	call   0x564720
  57d942:	8b c8                	mov    ecx,eax
  57d944:	e8 87 b7 f7 ff       	call   0x4f90d0
  57d949:	e8 22 81 eb ff       	call   0x435a70
  57d94e:	e9 25 03 00 00       	jmp    0x57dc78
  57d953:	e8 d8 60 f8 ff       	call   0x503a30
  57d958:	e9 1b 03 00 00       	jmp    0x57dc78
  57d95d:	b9 d0 c4 5d 00       	mov    ecx,0x5dc4d0
  57d962:	e8 69 b7 f7 ff       	call   0x4f90d0
  57d967:	e8 b4 ea fe ff       	call   0x56c420
  57d96c:	e9 07 03 00 00       	jmp    0x57dc78
  57d971:	b9 e0 c4 5d 00       	mov    ecx,0x5dc4e0
  57d976:	e8 55 b7 f7 ff       	call   0x4f90d0
  57d97b:	e8 c0 f9 f8 ff       	call   0x50d340
  57d980:	e8 db d5 f8 ff       	call   0x50af60

  57da9e:	e9 d5 01 00 00       	jmp    0x57dc78
  57daa3:	68 16 c6 58 00       	push   0x58c616
  57daa8:	33 d2                	xor    edx,edx
  57daaa:	b9 aa 01 00 00       	mov    ecx,0x1aa
  57daaf:	e8 9c 5e fe ff       	call   0x563950
  57dab4:	83 c4 04             	add    esp,0x4
  57dab7:	e9 bc 01 00 00       	jmp    0x57dc78
  57dabc:	68 16 c6 58 00       	push   0x58c616
  57dac1:	33 d2                	xor    edx,edx
  57dac3:	b9 bc 02 00 00       	mov    ecx,0x2bc
  57dac8:	e8 83 5e fe ff       	call   0x563950
  57dacd:	83 c4 04             	add    esp,0x4
  57dad0:	e9 a3 01 00 00       	jmp    0x57dc78
  57dad5:	b9 00 c5 5d 00       	mov    ecx,0x5dc500
  57dada:	e8 f1 b5 f7 ff       	call   0x4f90d0
  57dadf:	e8 2c ed fe ff       	call   0x56c810
  57dae4:	e9 8f 01 00 00       	jmp    0x57dc78

  57dabc:	68 16 c6 58 00       	push   0x58c616
  57dac1:	33 d2                	xor    edx,edx
  57dac3:	b9 bc 02 00 00       	mov    ecx,0x2bc
  57dac8:	e8 83 5e fe ff       	call   0x563950
  57dacd:	83 c4 04             	add    esp,0x4
  57dad0:	e9 a3 01 00 00       	jmp    0x57dc78
  57dad5:	b9 00 c5 5d 00       	mov    ecx,0x5dc500
  57dada:	e8 f1 b5 f7 ff       	call   0x4f90d0
  57dadf:	e8 2c ed fe ff       	call   0x56c810
  57dae4:	e9 8f 01 00 00       	jmp    0x57dc78
  57dae9:	33 d2                	xor    edx,edx
  57daeb:	8d 4a 69             	lea    ecx,[edx+0x69]
  57daee:	e8 2d 6c fe ff       	call   0x564720
  57daf3:	8b c8                	mov    ecx,eax
  57daf5:	e8 d6 b5 f7 ff       	call   0x4f90d0
  57dafa:	e8 31 b3 ed ff       	call   0x458e30
  57daff:	e9 74 01 00 00       	jmp    0x57dc78

  57db51:	e8 ba 89 f7 ff       	call   0x4f6510
  57db56:	b9 68 c5 5d 00       	mov    ecx,0x5dc568
  57db5b:	e8 b0 89 f7 ff       	call   0x4f6510
  57db60:	e9 13 01 00 00       	jmp    0x57dc78
  57db65:	68 16 c6 58 00       	push   0x58c616
  57db6a:	33 d2                	xor    edx,edx
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

  57db94:	b1 12                	mov    cl,0x12
  57db96:	e8 85 9c f7 ff       	call   0x4f7820
  57db9b:	84 c0                	test   al,al
  57db9d:	0f 84 d5 00 00 00    	je     0x57dc78
  57dba3:	8b 15 34 1c 6d 0a    	mov    edx,DWORD PTR ds:0xa6d1c34
  57dba9:	8b 0d 3c bd 72 0a    	mov    ecx,DWORD PTR ds:0xa72bd3c
  57dbaf:	6a 01                	push   0x1
  57dbb1:	e8 5a a5 f8 ff       	call   0x508110
  57dbb6:	83 c4 04             	add    esp,0x4
  57dbb9:	e9 ba 00 00 00       	jmp    0x57dc78
  57dbbe:	33 d2                	xor    edx,edx
  57dbc0:	8d 4a 3a             	lea    ecx,[edx+0x3a]
  57dbc3:	e8 58 6b fe ff       	call   0x564720
  57dbc8:	8b c8                	mov    ecx,eax
  57dbca:	e8 01 b5 f7 ff       	call   0x4f90d0
  57dbcf:	8b 15 40 bd 72 0a    	mov    edx,DWORD PTR ds:0xa72bd40
  57dbd5:	8b 0d 9c 1c 6d 0a    	mov    ecx,DWORD PTR ds:0xa6d1c9c

  57dbc0:	8d 4a 3a             	lea    ecx,[edx+0x3a]
  57dbc3:	e8 58 6b fe ff       	call   0x564720
  57dbc8:	8b c8                	mov    ecx,eax
  57dbca:	e8 01 b5 f7 ff       	call   0x4f90d0
  57dbcf:	8b 15 40 bd 72 0a    	mov    edx,DWORD PTR ds:0xa72bd40
  57dbd5:	8b 0d 9c 1c 6d 0a    	mov    ecx,DWORD PTR ds:0xa6d1c9c
  57dbdb:	6a 01                	push   0x1
  57dbdd:	e8 2e a5 f8 ff       	call   0x508110
  57dbe2:	83 c4 04             	add    esp,0x4
  57dbe5:	e9 8e 00 00 00       	jmp    0x57dc78
  57dbea:	33 d2                	xor    edx,edx
  57dbec:	8d 4a 6f             	lea    ecx,[edx+0x6f]
  57dbef:	e8 2c 6b fe ff       	call   0x564720
  57dbf4:	8b c8                	mov    ecx,eax
  57dbf6:	e8 d5 b4 f7 ff       	call   0x4f90d0
  57dbfb:	33 d2                	xor    edx,edx
  57dbfd:	33 c9                	xor    ecx,ecx

  57dc0d:	75 69                	jne    0x57dc78
  57dc0f:	8a cb                	mov    cl,bl
  57dc11:	e8 0a 4b fb ff       	call   0x532720
  57dc16:	eb 60                	jmp    0x57dc78
  57dc18:	6a 00                	push   0x0
  57dc1a:	33 d2                	xor    edx,edx
  57dc1c:	b9 20 03 00 00       	mov    ecx,0x320
  57dc21:	e8 2a 5d fe ff       	call   0x563950
  57dc26:	83 c4 04             	add    esp,0x4
  57dc29:	eb 4d                	jmp    0x57dc78
  57dc2b:	33 d2                	xor    edx,edx
  57dc2d:	8d 4a 63             	lea    ecx,[edx+0x63]
  57dc30:	e8 eb 6a fe ff       	call   0x564720
  57dc35:	8b c8                	mov    ecx,eax
  57dc37:	e8 94 b4 f7 ff       	call   0x4f90d0
  57dc3c:	e8 0f 57 f2 ff       	call   0x4a3350
  57dc41:	a2 e3 cc 58 04       	mov    ds:0x458cce3,al

  57dc35:	8b c8                	mov    ecx,eax
  57dc37:	e8 94 b4 f7 ff       	call   0x4f90d0
  57dc3c:	e8 0f 57 f2 ff       	call   0x4a3350
  57dc41:	a2 e3 cc 58 04       	mov    ds:0x458cce3,al
  57dc46:	eb 30                	jmp    0x57dc78
  57dc48:	bb 25 04 00 00       	mov    ebx,0x425
  57dc4d:	eb 35                	jmp    0x57dc84
  57dc4f:	e8 1c 59 f2 ff       	call   0x4a3570
  57dc54:	eb 22                	jmp    0x57dc78
  57dc56:	c6 05 e7 bc 72 0a 01 	mov    BYTE PTR ds:0xa72bce7,0x1
  57dc5d:	b9 0a 00 00 00       	mov    ecx,0xa
  57dc62:	e8 e9 88 f0 ff       	call   0x486550
  57dc67:	b9 ec c4 5d 00       	mov    ecx,0x5dc4ec
  57dc6c:	c6 05 e3 cc 58 04 01 	mov    BYTE PTR ds:0x458cce3,0x1
  57dc73:	e8 58 b4 f7 ff       	call   0x4f90d0
  57dc78:	81 fb e8 03 00 00    	cmp    ebx,0x3e8
  57dc7e:	0f 8c 12 04 00 00    	jl     0x57e096

