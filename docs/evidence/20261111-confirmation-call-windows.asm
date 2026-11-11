  42c8b0:	ff 15 00 c5 58 00    	call   DWORD PTR ds:0x58c500
  42c8b6:	83 c4 0c             	add    esp,0xc
  42c8b9:	50                   	push   eax
  42c8ba:	8d 84 24 9c 00 00 00 	lea    eax,[esp+0x9c]
  42c8c1:	68 b0 21 59 00       	push   0x5921b0
  42c8c6:	50                   	push   eax
  42c8c7:	e8 04 48 fd ff       	call   0x4010d0
  42c8cc:	83 c4 0c             	add    esp,0xc
  42c8cf:	8d 8c 24 98 00 00 00 	lea    ecx,[esp+0x98]
  42c8d6:	e8 35 9c 0c 00       	call   0x4f6510
  42c8db:	33 d2                	xor    edx,edx
  42c8dd:	b9 e4 e1 58 00       	mov    ecx,0x58e1e4
  42c8e2:	e8 e9 ef fd ff       	call   0x40b8d0
  42c8e7:	83 7c 24 28 00       	cmp    DWORD PTR [esp+0x28],0x0
  42c8ec:	74 37                	je     0x42c925
  42c8ee:	b9 c8 21 59 00       	mov    ecx,0x5921c8
  42c8f3:	e8 18 9c 0c 00       	call   0x4f6510
  42c8f8:	b9 00 22 59 00       	mov    ecx,0x592200
  42c8fd:	e8 9e ef 0c 00       	call   0x4fb8a0
  42c902:	84 c0                	test   al,al
  42c904:	75 24                	jne    0x42c92a
  42c906:	b9 20 22 59 00       	mov    ecx,0x592220
  42c90b:	e8 00 9c 0c 00       	call   0x4f6510
  42c910:	5f                   	pop    edi
  42c911:	5e                   	pop    esi
  42c912:	5b                   	pop    ebx
  42c913:	8b 8c 24 90 04 00 00 	mov    ecx,DWORD PTR [esp+0x490]
  42c91a:	33 cc                	xor    ecx,esp

  42cdc6:	2b d0                	sub    edx,eax
  42cdc8:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [eax+eax*1+0x0]
  42cdcf:	00 
  42cdd0:	8a 08                	mov    cl,BYTE PTR [eax]
  42cdd2:	8d 40 01             	lea    eax,[eax+0x1]
  42cdd5:	88 4c 02 ff          	mov    BYTE PTR [edx+eax*1-0x1],cl
  42cdd9:	84 c9                	test   cl,cl
  42cddb:	75 f3                	jne    0x42cdd0
  42cddd:	8b b5 ec fb ff ff    	mov    esi,DWORD PTR [ebp-0x414]
  42cde3:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  42cde9:	50                   	push   eax
  42cdea:	68 80 22 59 00       	push   0x592280
  42cdef:	56                   	push   esi
  42cdf0:	e8 db 42 fd ff       	call   0x4010d0
  42cdf5:	83 c4 0c             	add    esp,0xc
  42cdf8:	8b ce                	mov    ecx,esi
  42cdfa:	e8 11 97 0c 00       	call   0x4f6510
  42cdff:	b9 b0 22 59 00       	mov    ecx,0x5922b0
  42ce04:	e8 97 ea 0c 00       	call   0x4fb8a0
  42ce09:	84 c0                	test   al,al
  42ce0b:	75 18                	jne    0x42ce25
  42ce0d:	a2 f6 21 61 00       	mov    ds:0x6121f6,al
  42ce12:	33 c0                	xor    eax,eax
  42ce14:	5f                   	pop    edi
  42ce15:	5e                   	pop    esi
  42ce16:	5b                   	pop    ebx
  42ce17:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  42ce1a:	33 cd                	xor    ecx,ebp

  489dcf:	89 84 24 80 29 00 00 	mov    DWORD PTR [esp+0x2980],eax
  489dd6:	66 a1 44 ce 59 00    	mov    ax,ds:0x59ce44
  489ddc:	66 0f d6 84 24 78 29 	movq   QWORD PTR [esp+0x2978],xmm0
  489de3:	00 00 
  489de5:	66 89 84 24 84 29 00 	mov    WORD PTR [esp+0x2984],ax
  489dec:	00 
  489ded:	eb 34                	jmp    0x489e23
  489def:	bb 1b 00 00 00       	mov    ebx,0x1b
  489df4:	8d 73 e6             	lea    esi,[ebx-0x1a]
  489df7:	e9 ad fe ff ff       	jmp    0x489ca9
  489dfc:	a1 58 ce 59 00       	mov    eax,ds:0x59ce58
  489e01:	0f 10 05 48 ce 59 00 	movups xmm0,XMMWORD PTR ds:0x59ce48
  489e08:	89 84 24 88 29 00 00 	mov    DWORD PTR [esp+0x2988],eax
  489e0f:	a0 5c ce 59 00       	mov    al,ds:0x59ce5c
  489e14:	0f 11 84 24 78 29 00 	movups XMMWORD PTR [esp+0x2978],xmm0
  489e1b:	00 
  489e1c:	88 84 24 8c 29 00 00 	mov    BYTE PTR [esp+0x298c],al
  489e23:	8d 8c 24 78 29 00 00 	lea    ecx,[esp+0x2978]
  489e2a:	e8 71 1a 07 00       	call   0x4fb8a0
  489e2f:	84 c0                	test   al,al
  489e31:	0f 85 e0 03 00 00    	jne    0x48a217
  489e37:	c7 05 4c f5 17 02 01 	mov    DWORD PTR ds:0x217f54c,0x1
  489e3e:	00 00 00 
  489e41:	eb 09                	jmp    0x489e4c
  489e43:	83 fe 01             	cmp    esi,0x1
  489e46:	0f 84 cb 03 00 00    	je     0x48a217
  489e4c:	80 7c 24 36 01       	cmp    BYTE PTR [esp+0x36],0x1
  489e51:	76 0f                	jbe    0x489e62

  450438:	5d                   	pop    ebp
  450439:	c3                   	ret
  45043a:	80 bd 48 fb ff ff 03 	cmp    BYTE PTR [ebp-0x4b8],0x3
  450441:	74 44                	je     0x450487
  450443:	8b 0c 9d d0 ac 72 0a 	mov    ecx,DWORD PTR [ebx*4+0xa72acd0]
  45044a:	ba 01 00 00 00       	mov    edx,0x1
  45044f:	6a 00                	push   0x0
  450451:	e8 ea 21 00 00       	call   0x452640
  450456:	83 c4 04             	add    esp,0x4
  450459:	50                   	push   eax
  45045a:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  450460:	68 70 8d 59 00       	push   0x598d70
  450465:	50                   	push   eax
  450466:	e8 65 0c fb ff       	call   0x4010d0
  45046b:	83 c4 0c             	add    esp,0xc
  45046e:	8d 8d f8 fb ff ff    	lea    ecx,[ebp-0x408]
  450474:	e8 97 60 0a 00       	call   0x4f6510
  450479:	b9 f4 54 59 00       	mov    ecx,0x5954f4
  45047e:	e8 1d b4 0a 00       	call   0x4fb8a0
  450483:	84 c0                	test   al,al
  450485:	74 1d                	je     0x4504a4
  450487:	f3 0f 10 0d 84 d6 5d 	movss  xmm1,DWORD PTR ds:0x5dd684
  45048e:	00 
  45048f:	8b cb                	mov    ecx,ebx
  450491:	e8 aa ed ff ff       	call   0x44f240
  450496:	8b cb                	mov    ecx,ebx
  450498:	e8 d3 a5 11 00       	call   0x56aa70
  45049d:	c6 05 e3 cc 58 04 01 	mov    BYTE PTR ds:0x458cce3,0x1

  4a02ba:	3a 11                	cmp    dl,BYTE PTR [ecx]
  4a02bc:	75 1a                	jne    0x4a02d8
  4a02be:	84 d2                	test   dl,dl
  4a02c0:	74 12                	je     0x4a02d4
  4a02c2:	8a 50 01             	mov    dl,BYTE PTR [eax+0x1]
  4a02c5:	3a 51 01             	cmp    dl,BYTE PTR [ecx+0x1]
  4a02c8:	75 0e                	jne    0x4a02d8
  4a02ca:	83 c0 02             	add    eax,0x2
  4a02cd:	83 c1 02             	add    ecx,0x2
  4a02d0:	84 d2                	test   dl,dl
  4a02d2:	75 e4                	jne    0x4a02b8
  4a02d4:	33 c0                	xor    eax,eax
  4a02d6:	eb 05                	jmp    0x4a02dd
  4a02d8:	1b c0                	sbb    eax,eax
  4a02da:	83 c8 01             	or     eax,0x1
  4a02dd:	85 c0                	test   eax,eax
  4a02df:	75 0f                	jne    0x4a02f0
  4a02e1:	b9 54 e5 59 00       	mov    ecx,0x59e554
  4a02e6:	e8 b5 b5 05 00       	call   0x4fb8a0
  4a02eb:	84 c0                	test   al,al
  4a02ed:	0f 45 fe             	cmovne edi,esi
  4a02f0:	b9 e0 ca 59 00       	mov    ecx,0x59cae0
  4a02f5:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  4a02fb:	0f 1f 44 00 00       	nop    DWORD PTR [eax+eax*1+0x0]
  4a0300:	8a 10                	mov    dl,BYTE PTR [eax]
  4a0302:	3a 11                	cmp    dl,BYTE PTR [ecx]
  4a0304:	75 1a                	jne    0x4a0320
  4a0306:	84 d2                	test   dl,dl

  4a03f2:	3a 11                	cmp    dl,BYTE PTR [ecx]
  4a03f4:	75 1a                	jne    0x4a0410
  4a03f6:	84 d2                	test   dl,dl
  4a03f8:	74 12                	je     0x4a040c
  4a03fa:	8a 50 01             	mov    dl,BYTE PTR [eax+0x1]
  4a03fd:	3a 51 01             	cmp    dl,BYTE PTR [ecx+0x1]
  4a0400:	75 0e                	jne    0x4a0410
  4a0402:	83 c0 02             	add    eax,0x2
  4a0405:	83 c1 02             	add    ecx,0x2
  4a0408:	84 d2                	test   dl,dl
  4a040a:	75 e4                	jne    0x4a03f0
  4a040c:	33 c0                	xor    eax,eax
  4a040e:	eb 05                	jmp    0x4a0415
  4a0410:	1b c0                	sbb    eax,eax
  4a0412:	83 c8 01             	or     eax,0x1
  4a0415:	85 c0                	test   eax,eax
  4a0417:	75 0e                	jne    0x4a0427
  4a0419:	b9 24 e5 59 00       	mov    ecx,0x59e524
  4a041e:	e8 7d b4 05 00       	call   0x4fb8a0
  4a0423:	84 c0                	test   al,al
  4a0425:	75 08                	jne    0x4a042f
  4a0427:	85 f6                	test   esi,esi
  4a0429:	0f 84 c7 fb ff ff    	je     0x49fff6
  4a042f:	8b d3                	mov    edx,ebx
  4a0431:	8b cf                	mov    ecx,edi
  4a0433:	e8 18 b6 07 00       	call   0x51ba50
  4a0438:	33 c0                	xor    eax,eax
  4a043a:	5f                   	pop    edi

  4a05d2:	3a 11                	cmp    dl,BYTE PTR [ecx]
  4a05d4:	75 1a                	jne    0x4a05f0
  4a05d6:	84 d2                	test   dl,dl
  4a05d8:	74 12                	je     0x4a05ec
  4a05da:	8a 50 01             	mov    dl,BYTE PTR [eax+0x1]
  4a05dd:	3a 51 01             	cmp    dl,BYTE PTR [ecx+0x1]
  4a05e0:	75 0e                	jne    0x4a05f0
  4a05e2:	83 c0 02             	add    eax,0x2
  4a05e5:	83 c1 02             	add    ecx,0x2
  4a05e8:	84 d2                	test   dl,dl
  4a05ea:	75 e4                	jne    0x4a05d0
  4a05ec:	33 c0                	xor    eax,eax
  4a05ee:	eb 05                	jmp    0x4a05f5
  4a05f0:	1b c0                	sbb    eax,eax
  4a05f2:	83 c8 01             	or     eax,0x1
  4a05f5:	85 c0                	test   eax,eax
  4a05f7:	75 0e                	jne    0x4a0607
  4a05f9:	b9 24 e5 59 00       	mov    ecx,0x59e524
  4a05fe:	e8 9d b2 05 00       	call   0x4fb8a0
  4a0603:	84 c0                	test   al,al
  4a0605:	75 08                	jne    0x4a060f
  4a0607:	85 ff                	test   edi,edi
  4a0609:	0f 84 e7 f9 ff ff    	je     0x49fff6
  4a060f:	8b d3                	mov    edx,ebx
  4a0611:	8b ce                	mov    ecx,esi
  4a0613:	e8 38 b4 07 00       	call   0x51ba50
  4a0618:	33 c0                	xor    eax,eax
  4a061a:	5f                   	pop    edi

  49fe3a:	5d                   	pop    ebp
  49fe3b:	c3                   	ret
  49fe3c:	8b d7                	mov    edx,edi
  49fe3e:	8b ce                	mov    ecx,esi
  49fe40:	e8 8b 2d 0e 00       	call   0x582bd0
  49fe45:	0f b6 c8             	movzx  ecx,al
  49fe48:	e8 83 e6 0b 00       	call   0x55e4d0
  49fe4d:	50                   	push   eax
  49fe4e:	8d 85 f4 fb ff ff    	lea    eax,[ebp-0x40c]
  49fe54:	68 40 e4 59 00       	push   0x59e440
  49fe59:	50                   	push   eax
  49fe5a:	e8 71 12 f6 ff       	call   0x4010d0
  49fe5f:	83 c4 0c             	add    esp,0xc
  49fe62:	8d 8d f4 fb ff ff    	lea    ecx,[ebp-0x40c]
  49fe68:	e8 a3 66 05 00       	call   0x4f6510
  49fe6d:	80 7d 08 00          	cmp    BYTE PTR [ebp+0x8],0x0
  49fe71:	74 1f                	je     0x49fe92
  49fe73:	b9 54 e4 59 00       	mov    ecx,0x59e454
  49fe78:	e8 23 ba 05 00       	call   0x4fb8a0
  49fe7d:	84 c0                	test   al,al
  49fe7f:	0f 95 c0             	setne  al
  49fe82:	5f                   	pop    edi
  49fe83:	5e                   	pop    esi
  49fe84:	8b 4d f8             	mov    ecx,DWORD PTR [ebp-0x8]
  49fe87:	33 cd                	xor    ecx,ebp
  49fe89:	e8 20 a2 0e 00       	call   0x58a0ae
  49fe8e:	8b e5                	mov    esp,ebp
  49fe90:	5d                   	pop    ebp

  431e34:	6a 00                	push   0x0
  431e36:	68 20 2d 59 00       	push   0x592d20
  431e3b:	a2 e7 bc 72 0a       	mov    ds:0xa72bce7,al
  431e40:	e8 fb 69 05 00       	call   0x488840
  431e45:	83 c4 0c             	add    esp,0xc
  431e48:	85 c0                	test   eax,eax
  431e4a:	0f 84 c1 01 00 00    	je     0x432011
  431e50:	6a 01                	push   0x1
  431e52:	68 b0 05 59 00       	push   0x5905b0
  431e57:	33 d2                	xor    edx,edx
  431e59:	33 c9                	xor    ecx,ecx
  431e5b:	e8 50 0b 0f 00       	call   0x5229b0
  431e60:	83 c4 08             	add    esp,0x8
  431e63:	b9 07 00 00 00       	mov    ecx,0x7
  431e68:	e8 33 ae 12 00       	call   0x55cca0
  431e6d:	83 3d a0 28 6d 0a 00 	cmp    DWORD PTR ds:0xa6d28a0,0x0
  431e74:	74 22                	je     0x431e98
  431e76:	b9 84 30 59 00       	mov    ecx,0x593084
  431e7b:	e8 20 9a 0c 00       	call   0x4fb8a0
  431e80:	8b bd b0 f6 ff ff    	mov    edi,DWORD PTR [ebp-0x950]
  431e86:	84 c0                	test   al,al
  431e88:	74 14                	je     0x431e9e
  431e8a:	ba 64 00 00 00       	mov    edx,0x64
  431e8f:	8b cf                	mov    ecx,edi
  431e91:	e8 7a e9 ff ff       	call   0x430810
  431e96:	eb 06                	jmp    0x431e9e
  431e98:	8b bd b0 f6 ff ff    	mov    edi,DWORD PTR [ebp-0x950]
  431e9e:	8b 9d b4 f6 ff ff    	mov    ebx,DWORD PTR [ebp-0x94c]

  431f3c:	eb da                	jmp    0x431f18
  431f3e:	83 fb 03             	cmp    ebx,0x3
  431f41:	75 10                	jne    0x431f53
  431f43:	8b bd a8 f6 ff ff    	mov    edi,DWORD PTR [ebp-0x958]
  431f49:	83 ff 02             	cmp    edi,0x2
  431f4c:	7e 53                	jle    0x431fa1
  431f4e:	8d 7b ff             	lea    edi,[ebx-0x1]
  431f51:	eb 4e                	jmp    0x431fa1
  431f53:	83 fb 02             	cmp    ebx,0x2
  431f56:	75 43                	jne    0x431f9b
  431f58:	8b c8                	mov    ecx,eax
  431f5a:	e8 81 d7 09 00       	call   0x4cf6e0
  431f5f:	8b d0                	mov    edx,eax
  431f61:	8b cf                	mov    ecx,edi
  431f63:	e8 a8 e8 ff ff       	call   0x430810
  431f68:	83 3d a0 28 6d 0a 00 	cmp    DWORD PTR ds:0xa6d28a0,0x0
  431f6f:	74 18                	je     0x431f89
  431f71:	b9 94 30 59 00       	mov    ecx,0x593094
  431f76:	e8 25 99 0c 00       	call   0x4fb8a0
  431f7b:	84 c0                	test   al,al
  431f7d:	74 0a                	je     0x431f89
  431f7f:	8d 53 30             	lea    edx,[ebx+0x30]
  431f82:	8b cf                	mov    ecx,edi
  431f84:	e8 87 e8 ff ff       	call   0x430810
  431f89:	83 bd b8 f6 ff ff 00 	cmp    DWORD PTR [ebp-0x948],0x0
  431f90:	8b bd a8 f6 ff ff    	mov    edi,DWORD PTR [ebp-0x958]
  431f96:	0f 44 fe             	cmove  edi,esi
  431f99:	eb 06                	jmp    0x431fa1

  4025ee:	76 68                	jbe    0x402658
  4025f0:	8b 85 88 f7 ff ff    	mov    eax,DWORD PTR [ebp-0x878]
  4025f6:	33 c9                	xor    ecx,ecx
  4025f8:	33 ff                	xor    edi,edi
  4025fa:	89 9d 88 f4 ff ff    	mov    DWORD PTR [ebp-0xb78],ebx
  402600:	89 8d d8 f3 ff ff    	mov    DWORD PTR [ebp-0xc28],ecx
  402606:	89 bd 98 f6 ff ff    	mov    DWORD PTR [ebp-0x968],edi
  40260c:	c7 85 38 f5 ff ff 01 	mov    DWORD PTR [ebp-0xac8],0x1
  402613:	00 00 00 
  402616:	83 f8 ff             	cmp    eax,0xffffffff
  402619:	0f 85 8d 00 00 00    	jne    0x4026ac
  40261f:	38 4d 0c             	cmp    BYTE PTR [ebp+0xc],cl
  402622:	0f 85 18 0a 00 00    	jne    0x403040
  402628:	b9 50 c7 58 00       	mov    ecx,0x58c750
  40262d:	e8 ce f4 15 00       	call   0x561b00
  402632:	8b c8                	mov    ecx,eax
  402634:	e8 d7 3e 0f 00       	call   0x4f6510
  402639:	b9 68 c7 58 00       	mov    ecx,0x58c768
  40263e:	e8 5d 92 0f 00       	call   0x4fb8a0
  402643:	84 c0                	test   al,al
  402645:	74 34                	je     0x40267b
  402647:	33 d2                	xor    edx,edx
  402649:	c7 85 60 f7 ff ff 01 	mov    DWORD PTR [ebp-0x8a0],0x1
  402650:	00 00 00 
  402653:	89 55 08             	mov    DWORD PTR [ebp+0x8],edx
  402656:	eb 48                	jmp    0x4026a0
  402658:	38 5d 0c             	cmp    BYTE PTR [ebp+0xc],bl
  40265b:	0f 85 87 00 00 00    	jne    0x4026e8

  51c8ba:	8b 4c 24 44          	mov    ecx,DWORD PTR [esp+0x44]
  51c8be:	e8 3d 0d ef ff       	call   0x40d600
  51c8c3:	85 c0                	test   eax,eax
  51c8c5:	75 3e                	jne    0x51c905
  51c8c7:	b9 40 dc 5a 00       	mov    ecx,0x5adc40
  51c8cc:	e8 5f 77 00 00       	call   0x524030
  51c8d1:	84 c0                	test   al,al
  51c8d3:	74 30                	je     0x51c905
  51c8d5:	8b 54 24 40          	mov    edx,DWORD PTR [esp+0x40]
  51c8d9:	8b ce                	mov    ecx,esi
  51c8db:	6a 00                	push   0x0
  51c8dd:	e8 de 08 00 00       	call   0x51d1c0
  51c8e2:	83 c4 04             	add    esp,0x4
  51c8e5:	85 c0                	test   eax,eax
  51c8e7:	74 1c                	je     0x51c905
  51c8e9:	b9 58 dc 5a 00       	mov    ecx,0x5adc58
  51c8ee:	e8 1d 9c fd ff       	call   0x4f6510
  51c8f3:	b9 a0 dc 5a 00       	mov    ecx,0x5adca0
  51c8f8:	e8 a3 ef fd ff       	call   0x4fb8a0
  51c8fd:	84 c0                	test   al,al
  51c8ff:	0f 84 fc fd ff ff    	je     0x51c701
  51c905:	8d 84 24 18 01 00 00 	lea    eax,[esp+0x118]
  51c90c:	50                   	push   eax
  51c90d:	8d 84 24 3c 40 00 00 	lea    eax,[esp+0x403c]
  51c914:	68 c0 dc 5a 00       	push   0x5adcc0
  51c919:	50                   	push   eax
  51c91a:	e8 b1 47 ee ff       	call   0x4010d0
  51c91f:	83 c4 0c             	add    esp,0xc

  4a18c2:	3a 11                	cmp    dl,BYTE PTR [ecx]
  4a18c4:	75 1a                	jne    0x4a18e0
  4a18c6:	84 d2                	test   dl,dl
  4a18c8:	74 12                	je     0x4a18dc
  4a18ca:	8a 50 01             	mov    dl,BYTE PTR [eax+0x1]
  4a18cd:	3a 51 01             	cmp    dl,BYTE PTR [ecx+0x1]
  4a18d0:	75 0e                	jne    0x4a18e0
  4a18d2:	83 c0 02             	add    eax,0x2
  4a18d5:	83 c1 02             	add    ecx,0x2
  4a18d8:	84 d2                	test   dl,dl
  4a18da:	75 e4                	jne    0x4a18c0
  4a18dc:	33 c0                	xor    eax,eax
  4a18de:	eb 05                	jmp    0x4a18e5
  4a18e0:	1b c0                	sbb    eax,eax
  4a18e2:	83 c8 01             	or     eax,0x1
  4a18e5:	85 c0                	test   eax,eax
  4a18e7:	75 0e                	jne    0x4a18f7
  4a18e9:	b9 f4 e8 59 00       	mov    ecx,0x59e8f4
  4a18ee:	e8 ad 9f 05 00       	call   0x4fb8a0
  4a18f3:	84 c0                	test   al,al
  4a18f5:	75 09                	jne    0x4a1900
  4a18f7:	83 fb 01             	cmp    ebx,0x1
  4a18fa:	0f 85 71 fe ff ff    	jne    0x4a1771
  4a1900:	8b d7                	mov    edx,edi
  4a1902:	8b ce                	mov    ecx,esi
  4a1904:	e8 37 a3 07 00       	call   0x51bc40
  4a1909:	85 c0                	test   eax,eax
  4a190b:	0f 85 50 0c 00 00    	jne    0x4a2561

  4a2512:	3a 11                	cmp    dl,BYTE PTR [ecx]
  4a2514:	75 1a                	jne    0x4a2530
  4a2516:	84 d2                	test   dl,dl
  4a2518:	74 12                	je     0x4a252c
  4a251a:	8a 50 01             	mov    dl,BYTE PTR [eax+0x1]
  4a251d:	3a 51 01             	cmp    dl,BYTE PTR [ecx+0x1]
  4a2520:	75 0e                	jne    0x4a2530
  4a2522:	83 c0 02             	add    eax,0x2
  4a2525:	83 c1 02             	add    ecx,0x2
  4a2528:	84 d2                	test   dl,dl
  4a252a:	75 e4                	jne    0x4a2510
  4a252c:	33 c0                	xor    eax,eax
  4a252e:	eb 05                	jmp    0x4a2535
  4a2530:	1b c0                	sbb    eax,eax
  4a2532:	83 c8 01             	or     eax,0x1
  4a2535:	85 c0                	test   eax,eax
  4a2537:	75 0e                	jne    0x4a2547
  4a2539:	b9 f4 e8 59 00       	mov    ecx,0x59e8f4
  4a253e:	e8 5d 93 05 00       	call   0x4fb8a0
  4a2543:	84 c0                	test   al,al
  4a2545:	75 09                	jne    0x4a2550
  4a2547:	83 fb 01             	cmp    ebx,0x1
  4a254a:	0f 85 21 0a 00 00    	jne    0x4a2f71
  4a2550:	8b d7                	mov    edx,edi
  4a2552:	8b ce                	mov    ecx,esi
  4a2554:	e8 e7 96 07 00       	call   0x51bc40
  4a2559:	85 c0                	test   eax,eax
  4a255b:	0f 84 10 0a 00 00    	je     0x4a2f71

  49f1d5:	f3 0f 59 05 44 d1 5d 	mulss  xmm0,DWORD PTR ds:0x5dd144
  49f1dc:	00 
  49f1dd:	0f 5a c0             	cvtps2pd xmm0,xmm0
  49f1e0:	6a 00                	push   0x0
  49f1e2:	8b d3                	mov    edx,ebx
  49f1e4:	8b ce                	mov    ecx,esi
  49f1e6:	f2 0f 59 05 d8 d2 5d 	mulsd  xmm0,QWORD PTR ds:0x5dd2d8
  49f1ed:	00 
  49f1ee:	66 0f 5a d0          	cvtpd2ps xmm2,xmm0
  49f1f2:	e8 49 32 ff ff       	call   0x492440
  49f1f7:	83 c4 04             	add    esp,0x4
  49f1fa:	84 c0                	test   al,al
  49f1fc:	74 44                	je     0x49f242
  49f1fe:	85 ff                	test   edi,edi
  49f200:	74 40                	je     0x49f242
  49f202:	b9 6c e2 59 00       	mov    ecx,0x59e26c
  49f207:	e8 04 73 05 00       	call   0x4f6510
  49f20c:	b9 98 e2 59 00       	mov    ecx,0x59e298
  49f211:	e8 8a c6 05 00       	call   0x4fb8a0
  49f216:	84 c0                	test   al,al
  49f218:	75 28                	jne    0x49f242
  49f21a:	b8 64 00 00 00       	mov    eax,0x64
  49f21f:	5f                   	pop    edi
  49f220:	5e                   	pop    esi
  49f221:	5b                   	pop    ebx
  49f222:	8b e5                	mov    esp,ebp
  49f224:	5d                   	pop    ebp
  49f225:	c3                   	ret

  51c061:	e8 0a f8 fd ff       	call   0x4fb870
  51c066:	8b cf                	mov    ecx,edi
  51c068:	e8 73 36 fb ff       	call   0x4cf6e0
  51c06d:	8b cf                	mov    ecx,edi
  51c06f:	8d 70 01             	lea    esi,[eax+0x1]
  51c072:	e8 69 36 fb ff       	call   0x4cf6e0
  51c077:	03 f0                	add    esi,eax
  51c079:	80 bd 8d fb ff ff 00 	cmp    BYTE PTR [ebp-0x473],0x0
  51c080:	0f 84 d6 01 00 00    	je     0x51c25c
  51c086:	3b f7                	cmp    esi,edi
  51c088:	0f 4d f7             	cmovge esi,edi
  51c08b:	8b ce                	mov    ecx,esi
  51c08d:	e8 5e ab fb ff       	call   0x4d6bf0
  51c092:	80 3d 54 b0 72 0a 01 	cmp    BYTE PTR ds:0xa72b054,0x1
  51c099:	0f 87 b3 01 00 00    	ja     0x51c252
  51c09f:	3b f7                	cmp    esi,edi
  51c0a1:	0f 8d ab 01 00 00    	jge    0x51c252
  51c0a7:	b9 14 db 5a 00       	mov    ecx,0x5adb14
  51c0ac:	e8 ef f7 fd ff       	call   0x4fb8a0
  51c0b1:	84 c0                	test   al,al
  51c0b3:	0f 84 ef fb ff ff    	je     0x51bca8
  51c0b9:	32 db                	xor    bl,bl
  51c0bb:	eb 13                	jmp    0x51c0d0
  51c0bd:	0f b6 c7             	movzx  eax,bh
  51c0c0:	03 f8                	add    edi,eax
  51c0c2:	b8 00 00 00 00       	mov    eax,0x0
  51c0c7:	0f 48 f8             	cmovs  edi,eax
  51c0ca:	89 bd 74 fb ff ff    	mov    DWORD PTR [ebp-0x48c],edi

  57d64e:	e8 3d 5c f8 ff       	call   0x503290
  57d653:	e8 88 c5 f1 ff       	call   0x499be0
  57d658:	c6 05 e3 cc 58 04 01 	mov    BYTE PTR ds:0x458cce3,0x1
  57d65f:	e9 b2 00 00 00       	jmp    0x57d716
  57d664:	68 16 c6 58 00       	push   0x58c616
  57d669:	33 d2                	xor    edx,edx
  57d66b:	b9 c4 01 00 00       	mov    ecx,0x1c4
  57d670:	e8 db 62 fe ff       	call   0x563950
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
  57d6b6:	b9 c7 01 00 00       	mov    ecx,0x1c7
  57d6bb:	e8 90 62 fe ff       	call   0x563950
  57d6c0:	83 c4 04             	add    esp,0x4

  44ccf5:	75 66                	jne    0x44cd5d
  44ccf7:	6a 00                	push   0x0
  44ccf9:	6a 01                	push   0x1
  44ccfb:	6a 00                	push   0x0
  44ccfd:	8b d3                	mov    edx,ebx
  44ccff:	83 c9 ff             	or     ecx,0xffffffff
  44cd02:	e8 b9 56 fb ff       	call   0x4023c0
  44cd07:	83 c4 0c             	add    esp,0xc
  44cd0a:	85 c0                	test   eax,eax
  44cd0c:	74 2b                	je     0x44cd39
  44cd0e:	80 7d ff 00          	cmp    BYTE PTR [ebp-0x1],0x0
  44cd12:	b8 01 00 00 00       	mov    eax,0x1
  44cd17:	0f 44 f0             	cmove  esi,eax
  44cd1a:	f6 45 08 02          	test   BYTE PTR [ebp+0x8],0x2
  44cd1e:	75 04                	jne    0x44cd24
  44cd20:	85 f6                	test   esi,esi
  44cd22:	75 26                	jne    0x44cd4a
  44cd24:	b9 70 86 59 00       	mov    ecx,0x598670
  44cd29:	e8 72 eb 0a 00       	call   0x4fb8a0
  44cd2e:	84 c0                	test   al,al
  44cd30:	74 44                	je     0x44cd76
  44cd32:	be 01 00 00 00       	mov    esi,0x1
  44cd37:	eb 11                	jmp    0x44cd4a
  44cd39:	80 7d ff 00          	cmp    BYTE PTR [ebp-0x1],0x0
  44cd3d:	75 07                	jne    0x44cd46
  44cd3f:	be 01 00 00 00       	mov    esi,0x1
  44cd44:	eb 04                	jmp    0x44cd4a
  44cd46:	85 f6                	test   esi,esi

  44ceb7:	a1 8c 0a 62 0a       	mov    eax,ds:0xa620a8c
  44cebc:	40                   	inc    eax
  44cebd:	a3 8c 0a 62 0a       	mov    ds:0xa620a8c,eax
  44cec2:	3b 05 dc b8 72 0a    	cmp    eax,DWORD PTR ds:0xa72b8dc
  44cec8:	7c 14                	jl     0x44cede
  44ceca:	c7 05 a8 97 5e 00 01 	mov    DWORD PTR ds:0x5e97a8,0x1
  44ced1:	00 00 00 
  44ced4:	c7 05 8c 0a 62 0a 00 	mov    DWORD PTR ds:0xa620a8c,0x0
  44cedb:	00 00 00 
  44cede:	83 c6 20             	add    esi,0x20
  44cee1:	81 fe 38 2c 6f 00    	cmp    esi,0x6f2c38
  44cee7:	0f 8c 03 ff ff ff    	jl     0x44cdf0
  44ceed:	8b 45 f0             	mov    eax,DWORD PTR [ebp-0x10]
  44cef0:	84 c0                	test   al,al
  44cef2:	74 2e                	je     0x44cf22
  44cef4:	b9 a0 86 59 00       	mov    ecx,0x5986a0
  44cef9:	e8 12 96 0a 00       	call   0x4f6510
  44cefe:	b9 e8 86 59 00       	mov    ecx,0x5986e8
  44cf03:	e8 98 e9 0a 00       	call   0x4fb8a0
  44cf08:	84 c0                	test   al,al
  44cf0a:	74 16                	je     0x44cf22
  44cf0c:	ff 35 40 bd 72 0a    	push   DWORD PTR ds:0xa72bd40
  44cf12:	8b 15 9c 1c 6d 0a    	mov    edx,DWORD PTR ds:0xa6d1c9c
  44cf18:	8b cb                	mov    ecx,ebx
  44cf1a:	e8 91 bf 00 00       	call   0x458eb0
  44cf1f:	83 c4 04             	add    esp,0x4
  44cf22:	e8 59 04 05 00       	call   0x49d380
  44cf27:	83 c9 ff             	or     ecx,0xffffffff

  4ab6a8:	e8 53 64 0b 00       	call   0x561b00
  4ab6ad:	50                   	push   eax
  4ab6ae:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  4ab6b4:	50                   	push   eax
  4ab6b5:	e8 16 5a f5 ff       	call   0x4010d0
  4ab6ba:	83 c4 0c             	add    esp,0xc
  4ab6bd:	8d 8d f8 fb ff ff    	lea    ecx,[ebp-0x408]
  4ab6c3:	e8 48 ae 04 00       	call   0x4f6510
  4ab6c8:	8b 56 f4             	mov    edx,DWORD PTR [esi-0xc]
  4ab6cb:	8b cb                	mov    ecx,ebx
  4ab6cd:	57                   	push   edi
  4ab6ce:	e8 ed 33 f9 ff       	call   0x43eac0
  4ab6d3:	83 c4 04             	add    esp,0x4
  4ab6d6:	e9 9a 00 00 00       	jmp    0x4ab775
  4ab6db:	8b 85 f0 fb ff ff    	mov    eax,DWORD PTR [ebp-0x410]
  4ab6e1:	85 c0                	test   eax,eax
  4ab6e3:	75 25                	jne    0x4ab70a
  4ab6e5:	b9 bc 01 5a 00       	mov    ecx,0x5a01bc
  4ab6ea:	e8 b1 01 05 00       	call   0x4fb8a0
  4ab6ef:	84 c0                	test   al,al
  4ab6f1:	74 0c                	je     0x4ab6ff
  4ab6f3:	c7 85 f0 fb ff ff 01 	mov    DWORD PTR [ebp-0x410],0x1
  4ab6fa:	00 00 00 
  4ab6fd:	eb 10                	jmp    0x4ab70f
  4ab6ff:	83 c8 ff             	or     eax,0xffffffff
  4ab702:	89 85 f0 fb ff ff    	mov    DWORD PTR [ebp-0x410],eax
  4ab708:	eb 6b                	jmp    0x4ab775
  4ab70a:	83 f8 01             	cmp    eax,0x1

  4e7581:	56                   	push   esi
  4e7582:	33 f6                	xor    esi,esi
  4e7584:	57                   	push   edi
  4e7585:	8b f9                	mov    edi,ecx
  4e7587:	8d 5e 01             	lea    ebx,[esi+0x1]
  4e758a:	85 ff                	test   edi,edi
  4e758c:	0f 85 d1 00 00 00    	jne    0x4e7663
  4e7592:	39 35 30 56 35 06    	cmp    DWORD PTR ds:0x6355630,esi
  4e7598:	89 0d 30 56 35 06    	mov    DWORD PTR ds:0x6355630,ecx
  4e759e:	0f 45 f3             	cmovne esi,ebx
  4e75a1:	89 0d 94 2c 5e 00    	mov    DWORD PTR ds:0x5e2c94,ecx
  4e75a7:	39 0d 98 40 78 0a    	cmp    DWORD PTR ds:0xa784098,ecx
  4e75ad:	89 0d b4 37 39 06    	mov    DWORD PTR ds:0x63937b4,ecx
  4e75b3:	b9 48 73 5a 00       	mov    ecx,0x5a7348
  4e75b8:	75 05                	jne    0x4e75bf
  4e75ba:	b9 68 73 5a 00       	mov    ecx,0x5a7368
  4e75bf:	e8 4c ef 00 00       	call   0x4f6510
  4e75c4:	b9 a0 73 5a 00       	mov    ecx,0x5a73a0
  4e75c9:	e8 d2 42 01 00       	call   0x4fb8a0
  4e75ce:	84 c0                	test   al,al
  4e75d0:	74 21                	je     0x4e75f3
  4e75d2:	83 3d 98 40 78 0a 00 	cmp    DWORD PTR ds:0xa784098,0x0
  4e75d9:	74 28                	je     0x4e7603
  4e75db:	b9 e0 73 5a 00       	mov    ecx,0x5a73e0
  4e75e0:	e8 2b ef 00 00       	call   0x4f6510
  4e75e5:	b9 28 74 5a 00       	mov    ecx,0x5a7428
  4e75ea:	e8 b1 42 01 00       	call   0x4fb8a0
  4e75ef:	84 c0                	test   al,al

  4e7598:	89 0d 30 56 35 06    	mov    DWORD PTR ds:0x6355630,ecx
  4e759e:	0f 45 f3             	cmovne esi,ebx
  4e75a1:	89 0d 94 2c 5e 00    	mov    DWORD PTR ds:0x5e2c94,ecx
  4e75a7:	39 0d 98 40 78 0a    	cmp    DWORD PTR ds:0xa784098,ecx
  4e75ad:	89 0d b4 37 39 06    	mov    DWORD PTR ds:0x63937b4,ecx
  4e75b3:	b9 48 73 5a 00       	mov    ecx,0x5a7348
  4e75b8:	75 05                	jne    0x4e75bf
  4e75ba:	b9 68 73 5a 00       	mov    ecx,0x5a7368
  4e75bf:	e8 4c ef 00 00       	call   0x4f6510
  4e75c4:	b9 a0 73 5a 00       	mov    ecx,0x5a73a0
  4e75c9:	e8 d2 42 01 00       	call   0x4fb8a0
  4e75ce:	84 c0                	test   al,al
  4e75d0:	74 21                	je     0x4e75f3
  4e75d2:	83 3d 98 40 78 0a 00 	cmp    DWORD PTR ds:0xa784098,0x0
  4e75d9:	74 28                	je     0x4e7603
  4e75db:	b9 e0 73 5a 00       	mov    ecx,0x5a73e0
  4e75e0:	e8 2b ef 00 00       	call   0x4f6510
  4e75e5:	b9 28 74 5a 00       	mov    ecx,0x5a7428
  4e75ea:	e8 b1 42 01 00       	call   0x4fb8a0
  4e75ef:	84 c0                	test   al,al
  4e75f1:	75 36                	jne    0x4e7629
  4e75f3:	b9 b0 73 5a 00       	mov    ecx,0x5a73b0
  4e75f8:	e8 13 ef 00 00       	call   0x4f6510
  4e75fd:	33 c0                	xor    eax,eax
  4e75ff:	5f                   	pop    edi
  4e7600:	5e                   	pop    esi
  4e7601:	5b                   	pop    ebx
  4e7602:	c3                   	ret

  4e75ce:	84 c0                	test   al,al
  4e75d0:	74 21                	je     0x4e75f3
  4e75d2:	83 3d 98 40 78 0a 00 	cmp    DWORD PTR ds:0xa784098,0x0
  4e75d9:	74 28                	je     0x4e7603
  4e75db:	b9 e0 73 5a 00       	mov    ecx,0x5a73e0
  4e75e0:	e8 2b ef 00 00       	call   0x4f6510
  4e75e5:	b9 28 74 5a 00       	mov    ecx,0x5a7428
  4e75ea:	e8 b1 42 01 00       	call   0x4fb8a0
  4e75ef:	84 c0                	test   al,al
  4e75f1:	75 36                	jne    0x4e7629
  4e75f3:	b9 b0 73 5a 00       	mov    ecx,0x5a73b0
  4e75f8:	e8 13 ef 00 00       	call   0x4f6510
  4e75fd:	33 c0                	xor    eax,eax
  4e75ff:	5f                   	pop    edi
  4e7600:	5e                   	pop    esi
  4e7601:	5b                   	pop    ebx
  4e7602:	c3                   	ret
  4e7603:	b9 44 74 5a 00       	mov    ecx,0x5a7444
  4e7608:	e8 93 42 01 00       	call   0x4fb8a0
  4e760d:	84 c0                	test   al,al
  4e760f:	75 52                	jne    0x4e7663
  4e7611:	b9 5c 74 5a 00       	mov    ecx,0x5a745c
  4e7616:	e8 f5 ee 00 00       	call   0x4f6510
  4e761b:	b9 8c 74 5a 00       	mov    ecx,0x5a748c
  4e7620:	e8 7b 42 01 00       	call   0x4fb8a0
  4e7625:	84 c0                	test   al,al
  4e7627:	74 3a                	je     0x4e7663
  4e7629:	c7 05 90 ba 72 0a 99 	mov    DWORD PTR ds:0xa72ba90,0xffffff99

  4e75e5:	b9 28 74 5a 00       	mov    ecx,0x5a7428
  4e75ea:	e8 b1 42 01 00       	call   0x4fb8a0
  4e75ef:	84 c0                	test   al,al
  4e75f1:	75 36                	jne    0x4e7629
  4e75f3:	b9 b0 73 5a 00       	mov    ecx,0x5a73b0
  4e75f8:	e8 13 ef 00 00       	call   0x4f6510
  4e75fd:	33 c0                	xor    eax,eax
  4e75ff:	5f                   	pop    edi
  4e7600:	5e                   	pop    esi
  4e7601:	5b                   	pop    ebx
  4e7602:	c3                   	ret
  4e7603:	b9 44 74 5a 00       	mov    ecx,0x5a7444
  4e7608:	e8 93 42 01 00       	call   0x4fb8a0
  4e760d:	84 c0                	test   al,al
  4e760f:	75 52                	jne    0x4e7663
  4e7611:	b9 5c 74 5a 00       	mov    ecx,0x5a745c
  4e7616:	e8 f5 ee 00 00       	call   0x4f6510
  4e761b:	b9 8c 74 5a 00       	mov    ecx,0x5a748c
  4e7620:	e8 7b 42 01 00       	call   0x4fb8a0
  4e7625:	84 c0                	test   al,al
  4e7627:	74 3a                	je     0x4e7663
  4e7629:	c7 05 90 ba 72 0a 99 	mov    DWORD PTR ds:0xa72ba90,0xffffff99
  4e7630:	ff ff ff 
  4e7633:	e8 b8 fd ff ff       	call   0x4e73f0
  4e7638:	8b 0d b4 37 39 06    	mov    ecx,DWORD PTR ds:0x63937b4
  4e763e:	85 f6                	test   esi,esi
  4e7640:	c7 05 d8 bc 5b 06 00 	mov    DWORD PTR ds:0x65bbcd8,0x0
  4e7647:	00 00 00 

  5220c7:	50                   	push   eax
  5220c8:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  5220ce:	68 c8 ee 5a 00       	push   0x5aeec8
  5220d3:	50                   	push   eax
  5220d4:	e8 f7 ef ed ff       	call   0x4010d0
  5220d9:	83 c4 0c             	add    esp,0xc
  5220dc:	8d 8d f8 fb ff ff    	lea    ecx,[ebp-0x408]
  5220e2:	e8 29 44 fd ff       	call   0x4f6510
  5220e7:	b9 e4 ee 5a 00       	mov    ecx,0x5aeee4
  5220ec:	89 35 4c 2a 62 0a    	mov    DWORD PTR ds:0xa622a4c,esi
  5220f2:	e8 09 fa 03 00       	call   0x561b00
  5220f7:	50                   	push   eax
  5220f8:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  5220fe:	68 f4 ee 5a 00       	push   0x5aeef4
  522103:	50                   	push   eax
  522104:	e8 c7 ef ed ff       	call   0x4010d0
  522109:	83 c4 0c             	add    esp,0xc
  52210c:	8d 8d f8 fb ff ff    	lea    ecx,[ebp-0x408]
  522112:	e8 89 97 fd ff       	call   0x4fb8a0
  522117:	84 c0                	test   al,al
  522119:	74 0a                	je     0x522125
  52211b:	8b 95 c8 fb ff ff    	mov    edx,DWORD PTR [ebp-0x438]
  522121:	8b ce                	mov    ecx,esi
  522123:	eb 0f                	jmp    0x522134
  522125:	e8 c6 58 fb ff       	call   0x4d79f0
  52212a:	83 f8 ff             	cmp    eax,0xffffffff
  52212d:	74 0a                	je     0x522139
  52212f:	8b d0                	mov    edx,eax

  44e636:	99                   	cdq
  44e637:	b9 03 00 00 00       	mov    ecx,0x3
  44e63c:	f7 f9                	idiv   ecx
  44e63e:	46                   	inc    esi
  44e63f:	83 fe 0a             	cmp    esi,0xa
  44e642:	0f 44 df             	cmove  ebx,edi
  44e645:	3b d3                	cmp    edx,ebx
  44e647:	74 e7                	je     0x44e630
  44e649:	8b 9d 50 fd ff ff    	mov    ebx,DWORD PTR [ebp-0x2b0]
  44e64f:	8b cb                	mov    ecx,ebx
  44e651:	e8 ea c6 00 00       	call   0x45ad40
  44e656:	8b b5 58 fd ff ff    	mov    esi,DWORD PTR [ebp-0x2a8]
  44e65c:	8b bd 64 fd ff ff    	mov    edi,DWORD PTR [ebp-0x29c]
  44e662:	eb 06                	jmp    0x44e66a
  44e664:	8b 9d 50 fd ff ff    	mov    ebx,DWORD PTR [ebp-0x2b0]
  44e66a:	83 3d a0 28 6d 0a 00 	cmp    DWORD PTR ds:0xa6d28a0,0x0
  44e671:	74 34                	je     0x44e6a7
  44e673:	b9 9c 8b 59 00       	mov    ecx,0x598b9c
  44e678:	e8 23 d2 0a 00       	call   0x4fb8a0
  44e67d:	84 c0                	test   al,al
  44e67f:	74 0c                	je     0x44e68d
  44e681:	ba 64 00 00 00       	mov    edx,0x64
  44e686:	8b cb                	mov    ecx,ebx
  44e688:	e8 b3 c6 00 00       	call   0x45ad40
  44e68d:	b9 ac 8b 59 00       	mov    ecx,0x598bac
  44e692:	e8 09 d2 0a 00       	call   0x4fb8a0
  44e697:	84 c0                	test   al,al
  44e699:	74 0c                	je     0x44e6a7

  44e647:	74 e7                	je     0x44e630
  44e649:	8b 9d 50 fd ff ff    	mov    ebx,DWORD PTR [ebp-0x2b0]
  44e64f:	8b cb                	mov    ecx,ebx
  44e651:	e8 ea c6 00 00       	call   0x45ad40
  44e656:	8b b5 58 fd ff ff    	mov    esi,DWORD PTR [ebp-0x2a8]
  44e65c:	8b bd 64 fd ff ff    	mov    edi,DWORD PTR [ebp-0x29c]
  44e662:	eb 06                	jmp    0x44e66a
  44e664:	8b 9d 50 fd ff ff    	mov    ebx,DWORD PTR [ebp-0x2b0]
  44e66a:	83 3d a0 28 6d 0a 00 	cmp    DWORD PTR ds:0xa6d28a0,0x0
  44e671:	74 34                	je     0x44e6a7
  44e673:	b9 9c 8b 59 00       	mov    ecx,0x598b9c
  44e678:	e8 23 d2 0a 00       	call   0x4fb8a0
  44e67d:	84 c0                	test   al,al
  44e67f:	74 0c                	je     0x44e68d
  44e681:	ba 64 00 00 00       	mov    edx,0x64
  44e686:	8b cb                	mov    ecx,ebx
  44e688:	e8 b3 c6 00 00       	call   0x45ad40
  44e68d:	b9 ac 8b 59 00       	mov    ecx,0x598bac
  44e692:	e8 09 d2 0a 00       	call   0x4fb8a0
  44e697:	84 c0                	test   al,al
  44e699:	74 0c                	je     0x44e6a7
  44e69b:	ba 0a 00 00 00       	mov    edx,0xa
  44e6a0:	8b cb                	mov    ecx,ebx
  44e6a2:	e8 99 c6 00 00       	call   0x45ad40
  44e6a7:	83 ff ff             	cmp    edi,0xffffffff
  44e6aa:	74 53                	je     0x44e6ff
  44e6ac:	8b 95 5c fd ff ff    	mov    edx,DWORD PTR [ebp-0x2a4]
  44e6b2:	83 fe ff             	cmp    esi,0xffffffff

  49f300:	33 c9                	xor    ecx,ecx
  49f302:	3b c3                	cmp    eax,ebx
  49f304:	0f 94 c1             	sete   cl
  49f307:	85 d1                	test   ecx,edx
  49f309:	0f 84 99 01 00 00    	je     0x49f4a8
  49f30f:	0f b6 46 f8          	movzx  eax,BYTE PTR [esi-0x8]
  49f313:	83 c0 fc             	add    eax,0xfffffffc
  49f316:	83 f8 59             	cmp    eax,0x59
  49f319:	0f 87 89 01 00 00    	ja     0x49f4a8
  49f31f:	0f b6 80 9c f5 49 00 	movzx  eax,BYTE PTR [eax+0x49f59c]
  49f326:	ff 24 85 88 f5 49 00 	jmp    DWORD PTR [eax*4+0x49f588]
  49f32d:	83 7d 14 00          	cmp    DWORD PTR [ebp+0x14],0x0
  49f331:	0f 84 fc fb ff ff    	je     0x49ef33
  49f337:	80 7e 04 32          	cmp    BYTE PTR [esi+0x4],0x32
  49f33b:	0f 87 67 01 00 00    	ja     0x49f4a8
  49f341:	b9 54 e3 59 00       	mov    ecx,0x59e354
  49f346:	e8 c5 71 05 00       	call   0x4f6510
  49f34b:	b9 90 e3 59 00       	mov    ecx,0x59e390
  49f350:	e8 4b c5 05 00       	call   0x4fb8a0
  49f355:	84 c0                	test   al,al
  49f357:	0f 84 d6 fb ff ff    	je     0x49ef33
  49f35d:	e9 46 01 00 00       	jmp    0x49f4a8
  49f362:	80 7e 14 64          	cmp    BYTE PTR [esi+0x14],0x64
  49f366:	0f 85 3c 01 00 00    	jne    0x49f4a8
  49f36c:	83 7d 14 00          	cmp    DWORD PTR [ebp+0x14],0x0
  49f370:	0f 84 bd fb ff ff    	je     0x49ef33
  49f376:	b9 ac e3 59 00       	mov    ecx,0x59e3ac
  49f37b:	e8 20 c5 05 00       	call   0x4fb8a0

  49f31f:	0f b6 80 9c f5 49 00 	movzx  eax,BYTE PTR [eax+0x49f59c]
  49f326:	ff 24 85 88 f5 49 00 	jmp    DWORD PTR [eax*4+0x49f588]
  49f32d:	83 7d 14 00          	cmp    DWORD PTR [ebp+0x14],0x0
  49f331:	0f 84 fc fb ff ff    	je     0x49ef33
  49f337:	80 7e 04 32          	cmp    BYTE PTR [esi+0x4],0x32
  49f33b:	0f 87 67 01 00 00    	ja     0x49f4a8
  49f341:	b9 54 e3 59 00       	mov    ecx,0x59e354
  49f346:	e8 c5 71 05 00       	call   0x4f6510
  49f34b:	b9 90 e3 59 00       	mov    ecx,0x59e390
  49f350:	e8 4b c5 05 00       	call   0x4fb8a0
  49f355:	84 c0                	test   al,al
  49f357:	0f 84 d6 fb ff ff    	je     0x49ef33
  49f35d:	e9 46 01 00 00       	jmp    0x49f4a8
  49f362:	80 7e 14 64          	cmp    BYTE PTR [esi+0x14],0x64
  49f366:	0f 85 3c 01 00 00    	jne    0x49f4a8
  49f36c:	83 7d 14 00          	cmp    DWORD PTR [ebp+0x14],0x0
  49f370:	0f 84 bd fb ff ff    	je     0x49ef33
  49f376:	b9 ac e3 59 00       	mov    ecx,0x59e3ac
  49f37b:	e8 20 c5 05 00       	call   0x4fb8a0
  49f380:	84 c0                	test   al,al
  49f382:	0f 84 ab fb ff ff    	je     0x49ef33
  49f388:	e9 1b 01 00 00       	jmp    0x49f4a8
  49f38d:	e8 ce cd fe ff       	call   0x48c160
  49f392:	85 c0                	test   eax,eax
  49f394:	0f 85 0e 01 00 00    	jne    0x49f4a8
  49f39a:	39 05 f0 40 78 0a    	cmp    DWORD PTR ds:0xa7840f0,eax
  49f3a0:	0f 85 82 01 00 00    	jne    0x49f528
  49f3a6:	8b 06                	mov    eax,DWORD PTR [esi]

  570afa:	83 c4 08             	add    esp,0x8
  570afd:	f2 0f 11 04 24       	movsd  QWORD PTR [esp],xmm0
  570b02:	68 0c a7 5d 00       	push   0x5da70c
  570b07:	50                   	push   eax
  570b08:	e8 c3 05 e9 ff       	call   0x4010d0
  570b0d:	8d 8c 24 38 0b 02 00 	lea    ecx,[esp+0x20b38]
  570b14:	e8 f7 59 f8 ff       	call   0x4f6510
  570b19:	0f be 05 d8 49 78 0a 	movsx  eax,BYTE PTR ds:0xa7849d8
  570b20:	50                   	push   eax
  570b21:	ff 35 dc 49 78 0a    	push   DWORD PTR ds:0xa7849dc
  570b27:	8d 84 24 40 0b 02 00 	lea    eax,[esp+0x20b40]
  570b2e:	68 20 a7 5d 00       	push   0x5da720
  570b33:	50                   	push   eax
  570b34:	e8 97 05 e9 ff       	call   0x4010d0
  570b39:	83 c4 20             	add    esp,0x20
  570b3c:	8d 8c 24 28 0b 02 00 	lea    ecx,[esp+0x20b28]
  570b43:	e8 c8 59 f8 ff       	call   0x4f6510
  570b48:	b9 40 a7 5d 00       	mov    ecx,0x5da740
  570b4d:	e8 4e ad f8 ff       	call   0x4fb8a0
  570b52:	84 c0                	test   al,al
  570b54:	74 2f                	je     0x570b85
  570b56:	a0 b2 49 78 0a       	mov    al,ds:0xa7849b2
  570b5b:	04 0f                	add    al,0xf
  570b5d:	a2 b2 49 78 0a       	mov    ds:0xa7849b2,al
  570b62:	3c 64                	cmp    al,0x64
  570b64:	0f 8c 55 be 00 00    	jl     0x57c9bf
  570b6a:	c6 05 b2 49 78 0a 00 	mov    BYTE PTR ds:0xa7849b2,0x0
  570b71:	5f                   	pop    edi

  570b4d:	e8 4e ad f8 ff       	call   0x4fb8a0
  570b52:	84 c0                	test   al,al
  570b54:	74 2f                	je     0x570b85
  570b56:	a0 b2 49 78 0a       	mov    al,ds:0xa7849b2
  570b5b:	04 0f                	add    al,0xf
  570b5d:	a2 b2 49 78 0a       	mov    ds:0xa7849b2,al
  570b62:	3c 64                	cmp    al,0x64
  570b64:	0f 8c 55 be 00 00    	jl     0x57c9bf
  570b6a:	c6 05 b2 49 78 0a 00 	mov    BYTE PTR ds:0xa7849b2,0x0
  570b71:	5f                   	pop    edi
  570b72:	5e                   	pop    esi
  570b73:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  570b7a:	33 cc                	xor    ecx,esp
  570b7c:	e8 2d 95 01 00       	call   0x58a0ae
  570b81:	8b e5                	mov    esp,ebp
  570b83:	5d                   	pop    ebp
  570b84:	c3                   	ret
  570b85:	b9 48 a7 5d 00       	mov    ecx,0x5da748
  570b8a:	e8 11 ad f8 ff       	call   0x4fb8a0
  570b8f:	0f b6 0d b1 49 78 0a 	movzx  ecx,BYTE PTR ds:0xa7849b1
  570b96:	84 c0                	test   al,al
  570b98:	be 32 00 00 00       	mov    esi,0x32
  570b9d:	0f 45 ce             	cmovne ecx,esi
  570ba0:	88 0d b1 49 78 0a    	mov    BYTE PTR ds:0xa7849b1,cl
  570ba6:	b9 50 a7 5d 00       	mov    ecx,0x5da750
  570bab:	e8 f0 ac f8 ff       	call   0x4fb8a0
  570bb0:	84 c0                	test   al,al
  570bb2:	74 0f                	je     0x570bc3

  570b64:	0f 8c 55 be 00 00    	jl     0x57c9bf
  570b6a:	c6 05 b2 49 78 0a 00 	mov    BYTE PTR ds:0xa7849b2,0x0
  570b71:	5f                   	pop    edi
  570b72:	5e                   	pop    esi
  570b73:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  570b7a:	33 cc                	xor    ecx,esp
  570b7c:	e8 2d 95 01 00       	call   0x58a0ae
  570b81:	8b e5                	mov    esp,ebp
  570b83:	5d                   	pop    ebp
  570b84:	c3                   	ret
  570b85:	b9 48 a7 5d 00       	mov    ecx,0x5da748
  570b8a:	e8 11 ad f8 ff       	call   0x4fb8a0
  570b8f:	0f b6 0d b1 49 78 0a 	movzx  ecx,BYTE PTR ds:0xa7849b1
  570b96:	84 c0                	test   al,al
  570b98:	be 32 00 00 00       	mov    esi,0x32
  570b9d:	0f 45 ce             	cmovne ecx,esi
  570ba0:	88 0d b1 49 78 0a    	mov    BYTE PTR ds:0xa7849b1,cl
  570ba6:	b9 50 a7 5d 00       	mov    ecx,0x5da750
  570bab:	e8 f0 ac f8 ff       	call   0x4fb8a0
  570bb0:	84 c0                	test   al,al
  570bb2:	74 0f                	je     0x570bc3
  570bb4:	c7 05 a8 49 78 0a dd 	mov    DWORD PTR ds:0xa7849a8,0xffffffdd
  570bbb:	ff ff ff 
  570bbe:	e9 89 00 00 00       	jmp    0x570c4c
  570bc3:	b9 60 a7 5d 00       	mov    ecx,0x5da760
  570bc8:	e8 d3 ac f8 ff       	call   0x4fb8a0
  570bcd:	84 c0                	test   al,al
  570bcf:	74 0c                	je     0x570bdd

  570b81:	8b e5                	mov    esp,ebp
  570b83:	5d                   	pop    ebp
  570b84:	c3                   	ret
  570b85:	b9 48 a7 5d 00       	mov    ecx,0x5da748
  570b8a:	e8 11 ad f8 ff       	call   0x4fb8a0
  570b8f:	0f b6 0d b1 49 78 0a 	movzx  ecx,BYTE PTR ds:0xa7849b1
  570b96:	84 c0                	test   al,al
  570b98:	be 32 00 00 00       	mov    esi,0x32
  570b9d:	0f 45 ce             	cmovne ecx,esi
  570ba0:	88 0d b1 49 78 0a    	mov    BYTE PTR ds:0xa7849b1,cl
  570ba6:	b9 50 a7 5d 00       	mov    ecx,0x5da750
  570bab:	e8 f0 ac f8 ff       	call   0x4fb8a0
  570bb0:	84 c0                	test   al,al
  570bb2:	74 0f                	je     0x570bc3
  570bb4:	c7 05 a8 49 78 0a dd 	mov    DWORD PTR ds:0xa7849a8,0xffffffdd
  570bbb:	ff ff ff 
  570bbe:	e9 89 00 00 00       	jmp    0x570c4c
  570bc3:	b9 60 a7 5d 00       	mov    ecx,0x5da760
  570bc8:	e8 d3 ac f8 ff       	call   0x4fb8a0
  570bcd:	84 c0                	test   al,al
  570bcf:	74 0c                	je     0x570bdd
  570bd1:	c7 05 c4 49 78 0a f6 	mov    DWORD PTR ds:0xa7849c4,0xfffffff6
  570bd8:	ff ff ff 
  570bdb:	eb 6f                	jmp    0x570c4c
  570bdd:	b9 6c a7 5d 00       	mov    ecx,0x5da76c
  570be2:	e8 b9 ac f8 ff       	call   0x4fb8a0
  570be7:	84 c0                	test   al,al
  570be9:	74 0c                	je     0x570bf7

  570b98:	be 32 00 00 00       	mov    esi,0x32
  570b9d:	0f 45 ce             	cmovne ecx,esi
  570ba0:	88 0d b1 49 78 0a    	mov    BYTE PTR ds:0xa7849b1,cl
  570ba6:	b9 50 a7 5d 00       	mov    ecx,0x5da750
  570bab:	e8 f0 ac f8 ff       	call   0x4fb8a0
  570bb0:	84 c0                	test   al,al
  570bb2:	74 0f                	je     0x570bc3
  570bb4:	c7 05 a8 49 78 0a dd 	mov    DWORD PTR ds:0xa7849a8,0xffffffdd
  570bbb:	ff ff ff 
  570bbe:	e9 89 00 00 00       	jmp    0x570c4c
  570bc3:	b9 60 a7 5d 00       	mov    ecx,0x5da760
  570bc8:	e8 d3 ac f8 ff       	call   0x4fb8a0
  570bcd:	84 c0                	test   al,al
  570bcf:	74 0c                	je     0x570bdd
  570bd1:	c7 05 c4 49 78 0a f6 	mov    DWORD PTR ds:0xa7849c4,0xfffffff6
  570bd8:	ff ff ff 
  570bdb:	eb 6f                	jmp    0x570c4c
  570bdd:	b9 6c a7 5d 00       	mov    ecx,0x5da76c
  570be2:	e8 b9 ac f8 ff       	call   0x4fb8a0
  570be7:	84 c0                	test   al,al
  570be9:	74 0c                	je     0x570bf7
  570beb:	c7 05 c4 49 78 0a 9c 	mov    DWORD PTR ds:0xa7849c4,0xffffff9c
  570bf2:	ff ff ff 
  570bf5:	eb 55                	jmp    0x570c4c
  570bf7:	b9 7c a7 5d 00       	mov    ecx,0x5da77c
  570bfc:	e8 9f ac f8 ff       	call   0x4fb8a0
  570c01:	84 c0                	test   al,al
  570c03:	74 19                	je     0x570c1e

  570bb4:	c7 05 a8 49 78 0a dd 	mov    DWORD PTR ds:0xa7849a8,0xffffffdd
  570bbb:	ff ff ff 
  570bbe:	e9 89 00 00 00       	jmp    0x570c4c
  570bc3:	b9 60 a7 5d 00       	mov    ecx,0x5da760
  570bc8:	e8 d3 ac f8 ff       	call   0x4fb8a0
  570bcd:	84 c0                	test   al,al
  570bcf:	74 0c                	je     0x570bdd
  570bd1:	c7 05 c4 49 78 0a f6 	mov    DWORD PTR ds:0xa7849c4,0xfffffff6
  570bd8:	ff ff ff 
  570bdb:	eb 6f                	jmp    0x570c4c
  570bdd:	b9 6c a7 5d 00       	mov    ecx,0x5da76c
  570be2:	e8 b9 ac f8 ff       	call   0x4fb8a0
  570be7:	84 c0                	test   al,al
  570be9:	74 0c                	je     0x570bf7
  570beb:	c7 05 c4 49 78 0a 9c 	mov    DWORD PTR ds:0xa7849c4,0xffffff9c
  570bf2:	ff ff ff 
  570bf5:	eb 55                	jmp    0x570c4c
  570bf7:	b9 7c a7 5d 00       	mov    ecx,0x5da77c
  570bfc:	e8 9f ac f8 ff       	call   0x4fb8a0
  570c01:	84 c0                	test   al,al
  570c03:	74 19                	je     0x570c1e
  570c05:	a0 ae 49 78 0a       	mov    al,ds:0xa7849ae
  570c0a:	3c 03                	cmp    al,0x3
  570c0c:	7d 07                	jge    0x570c15
  570c0e:	fe c0                	inc    al
  570c10:	a2 ae 49 78 0a       	mov    ds:0xa7849ae,al
  570c15:	c6 05 af 49 78 0a 03 	mov    BYTE PTR ds:0xa7849af,0x3
  570c1c:	eb 2e                	jmp    0x570c4c

  570be2:	e8 b9 ac f8 ff       	call   0x4fb8a0
  570be7:	84 c0                	test   al,al
  570be9:	74 0c                	je     0x570bf7
  570beb:	c7 05 c4 49 78 0a 9c 	mov    DWORD PTR ds:0xa7849c4,0xffffff9c
  570bf2:	ff ff ff 
  570bf5:	eb 55                	jmp    0x570c4c
  570bf7:	b9 7c a7 5d 00       	mov    ecx,0x5da77c
  570bfc:	e8 9f ac f8 ff       	call   0x4fb8a0
  570c01:	84 c0                	test   al,al
  570c03:	74 19                	je     0x570c1e
  570c05:	a0 ae 49 78 0a       	mov    al,ds:0xa7849ae
  570c0a:	3c 03                	cmp    al,0x3
  570c0c:	7d 07                	jge    0x570c15
  570c0e:	fe c0                	inc    al
  570c10:	a2 ae 49 78 0a       	mov    ds:0xa7849ae,al
  570c15:	c6 05 af 49 78 0a 03 	mov    BYTE PTR ds:0xa7849af,0x3
  570c1c:	eb 2e                	jmp    0x570c4c
  570c1e:	b9 88 a7 5d 00       	mov    ecx,0x5da788
  570c23:	e8 78 ac f8 ff       	call   0x4fb8a0
  570c28:	84 c0                	test   al,al
  570c2a:	74 20                	je     0x570c4c
  570c2c:	a0 ae 49 78 0a       	mov    al,ds:0xa7849ae
  570c31:	3c 03                	cmp    al,0x3
  570c33:	7d 09                	jge    0x570c3e
  570c35:	fe c0                	inc    al
  570c37:	a2 ae 49 78 0a       	mov    ds:0xa7849ae,al
  570c3c:	eb 07                	jmp    0x570c45
  570c3e:	c6 05 ae 49 78 0a 01 	mov    BYTE PTR ds:0xa7849ae,0x1

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
  57c7b3:	89 44 24 14          	mov    DWORD PTR [esp+0x14],eax
  57c7b7:	85 c0                	test   eax,eax
  57c7b9:	0f 88 00 02 00 00    	js     0x57c9bf
  57c7bf:	8b 0c 85 d0 ac 72 0a 	mov    ecx,DWORD PTR [eax*4+0xa72acd0]
  57c7c6:	e8 45 39 f4 ff       	call   0x4c0110
  57c7cb:	b9 6c c1 5d 00       	mov    ecx,0x5dc16c
  57c7d0:	e8 cb f0 f7 ff       	call   0x4fb8a0
  57c7d5:	84 c0                	test   al,al
  57c7d7:	74 41                	je     0x57c81a
  57c7d9:	b8 0a 00 00 00       	mov    eax,0xa
  57c7de:	8b d0                	mov    edx,eax
  57c7e0:	8b c8                	mov    ecx,eax
  57c7e2:	e8 c9 2d f9 ff       	call   0x50f5b0
  57c7e7:	50                   	push   eax
  57c7e8:	ff d6                	call   esi
  57c7ea:	8b 74 24 18          	mov    esi,DWORD PTR [esp+0x18]

  57c7d9:	b8 0a 00 00 00       	mov    eax,0xa
  57c7de:	8b d0                	mov    edx,eax
  57c7e0:	8b c8                	mov    ecx,eax
  57c7e2:	e8 c9 2d f9 ff       	call   0x50f5b0
  57c7e7:	50                   	push   eax
  57c7e8:	ff d6                	call   esi
  57c7ea:	8b 74 24 18          	mov    esi,DWORD PTR [esp+0x18]
  57c7ee:	83 c4 04             	add    esp,0x4
  57c7f1:	8b 0c b5 d0 ac 72 0a 	mov    ecx,DWORD PTR [esi*4+0xa72acd0]
  57c7f8:	81 e9 50 c3 00 00    	sub    ecx,0xc350
  57c7fe:	69 c9 ac 00 00 00    	imul   ecx,ecx,0xac
  57c804:	8d 91 a8 16 92 05    	lea    edx,[ecx+0x59216a8]
  57c80a:	8b c8                	mov    ecx,eax
  57c80c:	e8 2f 45 f4 ff       	call   0x4c0d40
  57c811:	80 8a a5 00 00 00 80 	or     BYTE PTR [edx+0xa5],0x80
  57c818:	eb 04                	jmp    0x57c81e
  57c81a:	8b 74 24 14          	mov    esi,DWORD PTR [esp+0x14]
  57c81e:	b9 7c c1 5d 00       	mov    ecx,0x5dc17c
  57c823:	e8 78 f0 f7 ff       	call   0x4fb8a0
  57c828:	84 c0                	test   al,al
  57c82a:	74 19                	je     0x57c845
  57c82c:	8b 04 b5 d0 ac 72 0a 	mov    eax,DWORD PTR [esi*4+0xa72acd0]
  57c833:	2d 50 c3 00 00       	sub    eax,0xc350
  57c838:	69 c0 ac 00 00 00    	imul   eax,eax,0xac
  57c83e:	c6 80 3b 17 92 05 01 	mov    BYTE PTR [eax+0x592173b],0x1
  57c845:	b9 88 c1 5d 00       	mov    ecx,0x5dc188
  57c84a:	e8 51 f0 f7 ff       	call   0x4fb8a0
  57c84f:	84 c0                	test   al,al

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
  577096:	e8 85 20 ea ff       	call   0x419120
  57709b:	8b f0                	mov    esi,eax
  57709d:	83 fe ff             	cmp    esi,0xffffffff
  5770a0:	0f 84 eb 01 00 00    	je     0x577291
  5770a6:	b9 28 b0 5d 00       	mov    ecx,0x5db028
  5770ab:	e8 f0 47 f8 ff       	call   0x4fb8a0
  5770b0:	84 c0                	test   al,al
  5770b2:	74 08                	je     0x5770bc
  5770b4:	56                   	push   esi
  5770b5:	6a 25                	push   0x25
  5770b7:	e9 5f 01 00 00       	jmp    0x57721b
  5770bc:	b9 58 b0 5d 00       	mov    ecx,0x5db058
  5770c1:	e8 da 47 f8 ff       	call   0x4fb8a0
  5770c6:	84 c0                	test   al,al
  5770c8:	74 08                	je     0x5770d2

  577078:	0f 84 13 02 00 00    	je     0x577291
  57707e:	ba 16 c6 58 00       	mov    edx,0x58c616
  577083:	b1 01                	mov    cl,0x1
  577085:	e8 96 07 f8 ff       	call   0x4f7820
  57708a:	8b 15 34 1c 6d 0a    	mov    edx,DWORD PTR ds:0xa6d1c34
  577090:	8b 0d 3c bd 72 0a    	mov    ecx,DWORD PTR ds:0xa72bd3c
  577096:	e8 85 20 ea ff       	call   0x419120
  57709b:	8b f0                	mov    esi,eax
  57709d:	83 fe ff             	cmp    esi,0xffffffff
  5770a0:	0f 84 eb 01 00 00    	je     0x577291
  5770a6:	b9 28 b0 5d 00       	mov    ecx,0x5db028
  5770ab:	e8 f0 47 f8 ff       	call   0x4fb8a0
  5770b0:	84 c0                	test   al,al
  5770b2:	74 08                	je     0x5770bc
  5770b4:	56                   	push   esi
  5770b5:	6a 25                	push   0x25
  5770b7:	e9 5f 01 00 00       	jmp    0x57721b
  5770bc:	b9 58 b0 5d 00       	mov    ecx,0x5db058
  5770c1:	e8 da 47 f8 ff       	call   0x4fb8a0
  5770c6:	84 c0                	test   al,al
  5770c8:	74 08                	je     0x5770d2
  5770ca:	56                   	push   esi
  5770cb:	6a 48                	push   0x48
  5770cd:	e9 49 01 00 00       	jmp    0x57721b
  5770d2:	b9 6c b0 5d 00       	mov    ecx,0x5db06c
  5770d7:	e8 c4 47 f8 ff       	call   0x4fb8a0
  5770dc:	84 c0                	test   al,al
  5770de:	74 08                	je     0x5770e8

  57709b:	8b f0                	mov    esi,eax
  57709d:	83 fe ff             	cmp    esi,0xffffffff
  5770a0:	0f 84 eb 01 00 00    	je     0x577291
  5770a6:	b9 28 b0 5d 00       	mov    ecx,0x5db028
  5770ab:	e8 f0 47 f8 ff       	call   0x4fb8a0
  5770b0:	84 c0                	test   al,al
  5770b2:	74 08                	je     0x5770bc
  5770b4:	56                   	push   esi
  5770b5:	6a 25                	push   0x25
  5770b7:	e9 5f 01 00 00       	jmp    0x57721b
  5770bc:	b9 58 b0 5d 00       	mov    ecx,0x5db058
  5770c1:	e8 da 47 f8 ff       	call   0x4fb8a0
  5770c6:	84 c0                	test   al,al
  5770c8:	74 08                	je     0x5770d2
  5770ca:	56                   	push   esi
  5770cb:	6a 48                	push   0x48
  5770cd:	e9 49 01 00 00       	jmp    0x57721b
  5770d2:	b9 6c b0 5d 00       	mov    ecx,0x5db06c
  5770d7:	e8 c4 47 f8 ff       	call   0x4fb8a0
  5770dc:	84 c0                	test   al,al
  5770de:	74 08                	je     0x5770e8
  5770e0:	56                   	push   esi
  5770e1:	6a 34                	push   0x34
  5770e3:	e9 33 01 00 00       	jmp    0x57721b
  5770e8:	b9 7c b0 5d 00       	mov    ecx,0x5db07c
  5770ed:	e8 ae 47 f8 ff       	call   0x4fb8a0
  5770f2:	84 c0                	test   al,al
  5770f4:	74 08                	je     0x5770fe

  5770b4:	56                   	push   esi
  5770b5:	6a 25                	push   0x25
  5770b7:	e9 5f 01 00 00       	jmp    0x57721b
  5770bc:	b9 58 b0 5d 00       	mov    ecx,0x5db058
  5770c1:	e8 da 47 f8 ff       	call   0x4fb8a0
  5770c6:	84 c0                	test   al,al
  5770c8:	74 08                	je     0x5770d2
  5770ca:	56                   	push   esi
  5770cb:	6a 48                	push   0x48
  5770cd:	e9 49 01 00 00       	jmp    0x57721b
  5770d2:	b9 6c b0 5d 00       	mov    ecx,0x5db06c
  5770d7:	e8 c4 47 f8 ff       	call   0x4fb8a0
  5770dc:	84 c0                	test   al,al
  5770de:	74 08                	je     0x5770e8
  5770e0:	56                   	push   esi
  5770e1:	6a 34                	push   0x34
  5770e3:	e9 33 01 00 00       	jmp    0x57721b
  5770e8:	b9 7c b0 5d 00       	mov    ecx,0x5db07c
  5770ed:	e8 ae 47 f8 ff       	call   0x4fb8a0
  5770f2:	84 c0                	test   al,al
  5770f4:	74 08                	je     0x5770fe
  5770f6:	56                   	push   esi
  5770f7:	6a 33                	push   0x33
  5770f9:	e9 1d 01 00 00       	jmp    0x57721b
  5770fe:	b9 7c b0 5d 00       	mov    ecx,0x5db07c
  577103:	e8 98 47 f8 ff       	call   0x4fb8a0
  577108:	84 c0                	test   al,al
  57710a:	74 08                	je     0x577114

  5770ca:	56                   	push   esi
  5770cb:	6a 48                	push   0x48
  5770cd:	e9 49 01 00 00       	jmp    0x57721b
  5770d2:	b9 6c b0 5d 00       	mov    ecx,0x5db06c
  5770d7:	e8 c4 47 f8 ff       	call   0x4fb8a0
  5770dc:	84 c0                	test   al,al
  5770de:	74 08                	je     0x5770e8
  5770e0:	56                   	push   esi
  5770e1:	6a 34                	push   0x34
  5770e3:	e9 33 01 00 00       	jmp    0x57721b
  5770e8:	b9 7c b0 5d 00       	mov    ecx,0x5db07c
  5770ed:	e8 ae 47 f8 ff       	call   0x4fb8a0
  5770f2:	84 c0                	test   al,al
  5770f4:	74 08                	je     0x5770fe
  5770f6:	56                   	push   esi
  5770f7:	6a 33                	push   0x33
  5770f9:	e9 1d 01 00 00       	jmp    0x57721b
  5770fe:	b9 7c b0 5d 00       	mov    ecx,0x5db07c
  577103:	e8 98 47 f8 ff       	call   0x4fb8a0
  577108:	84 c0                	test   al,al
  57710a:	74 08                	je     0x577114
  57710c:	56                   	push   esi
  57710d:	6a 33                	push   0x33
  57710f:	e9 07 01 00 00       	jmp    0x57721b
  577114:	b9 88 b0 5d 00       	mov    ecx,0x5db088
  577119:	e8 82 47 f8 ff       	call   0x4fb8a0
  57711e:	84 c0                	test   al,al
  577120:	74 08                	je     0x57712a

  5770e0:	56                   	push   esi
  5770e1:	6a 34                	push   0x34
  5770e3:	e9 33 01 00 00       	jmp    0x57721b
  5770e8:	b9 7c b0 5d 00       	mov    ecx,0x5db07c
  5770ed:	e8 ae 47 f8 ff       	call   0x4fb8a0
  5770f2:	84 c0                	test   al,al
  5770f4:	74 08                	je     0x5770fe
  5770f6:	56                   	push   esi
  5770f7:	6a 33                	push   0x33
  5770f9:	e9 1d 01 00 00       	jmp    0x57721b
  5770fe:	b9 7c b0 5d 00       	mov    ecx,0x5db07c
  577103:	e8 98 47 f8 ff       	call   0x4fb8a0
  577108:	84 c0                	test   al,al
  57710a:	74 08                	je     0x577114
  57710c:	56                   	push   esi
  57710d:	6a 33                	push   0x33
  57710f:	e9 07 01 00 00       	jmp    0x57721b
  577114:	b9 88 b0 5d 00       	mov    ecx,0x5db088
  577119:	e8 82 47 f8 ff       	call   0x4fb8a0
  57711e:	84 c0                	test   al,al
  577120:	74 08                	je     0x57712a
  577122:	56                   	push   esi
  577123:	6a 47                	push   0x47
  577125:	e9 f1 00 00 00       	jmp    0x57721b
  57712a:	b9 94 b0 5d 00       	mov    ecx,0x5db094
  57712f:	e8 6c 47 f8 ff       	call   0x4fb8a0
  577134:	84 c0                	test   al,al
  577136:	74 08                	je     0x577140

  5770f6:	56                   	push   esi
  5770f7:	6a 33                	push   0x33
  5770f9:	e9 1d 01 00 00       	jmp    0x57721b
  5770fe:	b9 7c b0 5d 00       	mov    ecx,0x5db07c
  577103:	e8 98 47 f8 ff       	call   0x4fb8a0
  577108:	84 c0                	test   al,al
  57710a:	74 08                	je     0x577114
  57710c:	56                   	push   esi
  57710d:	6a 33                	push   0x33
  57710f:	e9 07 01 00 00       	jmp    0x57721b
  577114:	b9 88 b0 5d 00       	mov    ecx,0x5db088
  577119:	e8 82 47 f8 ff       	call   0x4fb8a0
  57711e:	84 c0                	test   al,al
  577120:	74 08                	je     0x57712a
  577122:	56                   	push   esi
  577123:	6a 47                	push   0x47
  577125:	e9 f1 00 00 00       	jmp    0x57721b
  57712a:	b9 94 b0 5d 00       	mov    ecx,0x5db094
  57712f:	e8 6c 47 f8 ff       	call   0x4fb8a0
  577134:	84 c0                	test   al,al
  577136:	74 08                	je     0x577140
  577138:	56                   	push   esi
  577139:	6a 32                	push   0x32
  57713b:	e9 db 00 00 00       	jmp    0x57721b
  577140:	b9 a4 b0 5d 00       	mov    ecx,0x5db0a4
  577145:	e8 56 47 f8 ff       	call   0x4fb8a0
  57714a:	84 c0                	test   al,al
  57714c:	74 08                	je     0x577156

  57710c:	56                   	push   esi
  57710d:	6a 33                	push   0x33
  57710f:	e9 07 01 00 00       	jmp    0x57721b
  577114:	b9 88 b0 5d 00       	mov    ecx,0x5db088
  577119:	e8 82 47 f8 ff       	call   0x4fb8a0
  57711e:	84 c0                	test   al,al
  577120:	74 08                	je     0x57712a
  577122:	56                   	push   esi
  577123:	6a 47                	push   0x47
  577125:	e9 f1 00 00 00       	jmp    0x57721b
  57712a:	b9 94 b0 5d 00       	mov    ecx,0x5db094
  57712f:	e8 6c 47 f8 ff       	call   0x4fb8a0
  577134:	84 c0                	test   al,al
  577136:	74 08                	je     0x577140
  577138:	56                   	push   esi
  577139:	6a 32                	push   0x32
  57713b:	e9 db 00 00 00       	jmp    0x57721b
  577140:	b9 a4 b0 5d 00       	mov    ecx,0x5db0a4
  577145:	e8 56 47 f8 ff       	call   0x4fb8a0
  57714a:	84 c0                	test   al,al
  57714c:	74 08                	je     0x577156
  57714e:	56                   	push   esi
  57714f:	6a 64                	push   0x64
  577151:	e9 c5 00 00 00       	jmp    0x57721b
  577156:	b9 b4 b0 5d 00       	mov    ecx,0x5db0b4
  57715b:	e8 40 47 f8 ff       	call   0x4fb8a0
  577160:	84 c0                	test   al,al
  577162:	74 08                	je     0x57716c

  577122:	56                   	push   esi
  577123:	6a 47                	push   0x47
  577125:	e9 f1 00 00 00       	jmp    0x57721b
  57712a:	b9 94 b0 5d 00       	mov    ecx,0x5db094
  57712f:	e8 6c 47 f8 ff       	call   0x4fb8a0
  577134:	84 c0                	test   al,al
  577136:	74 08                	je     0x577140
  577138:	56                   	push   esi
  577139:	6a 32                	push   0x32
  57713b:	e9 db 00 00 00       	jmp    0x57721b
  577140:	b9 a4 b0 5d 00       	mov    ecx,0x5db0a4
  577145:	e8 56 47 f8 ff       	call   0x4fb8a0
  57714a:	84 c0                	test   al,al
  57714c:	74 08                	je     0x577156
  57714e:	56                   	push   esi
  57714f:	6a 64                	push   0x64
  577151:	e9 c5 00 00 00       	jmp    0x57721b
  577156:	b9 b4 b0 5d 00       	mov    ecx,0x5db0b4
  57715b:	e8 40 47 f8 ff       	call   0x4fb8a0
  577160:	84 c0                	test   al,al
  577162:	74 08                	je     0x57716c
  577164:	56                   	push   esi
  577165:	6a 26                	push   0x26
  577167:	e9 af 00 00 00       	jmp    0x57721b
  57716c:	b9 c4 b0 5d 00       	mov    ecx,0x5db0c4
  577171:	e8 2a 47 f8 ff       	call   0x4fb8a0
  577176:	84 c0                	test   al,al
  577178:	74 08                	je     0x577182

  577138:	56                   	push   esi
  577139:	6a 32                	push   0x32
  57713b:	e9 db 00 00 00       	jmp    0x57721b
  577140:	b9 a4 b0 5d 00       	mov    ecx,0x5db0a4
  577145:	e8 56 47 f8 ff       	call   0x4fb8a0
  57714a:	84 c0                	test   al,al
  57714c:	74 08                	je     0x577156
  57714e:	56                   	push   esi
  57714f:	6a 64                	push   0x64
  577151:	e9 c5 00 00 00       	jmp    0x57721b
  577156:	b9 b4 b0 5d 00       	mov    ecx,0x5db0b4
  57715b:	e8 40 47 f8 ff       	call   0x4fb8a0
  577160:	84 c0                	test   al,al
  577162:	74 08                	je     0x57716c
  577164:	56                   	push   esi
  577165:	6a 26                	push   0x26
  577167:	e9 af 00 00 00       	jmp    0x57721b
  57716c:	b9 c4 b0 5d 00       	mov    ecx,0x5db0c4
  577171:	e8 2a 47 f8 ff       	call   0x4fb8a0
  577176:	84 c0                	test   al,al
  577178:	74 08                	je     0x577182
  57717a:	56                   	push   esi
  57717b:	6a 23                	push   0x23
  57717d:	e9 99 00 00 00       	jmp    0x57721b
  577182:	b9 d8 b0 5d 00       	mov    ecx,0x5db0d8
  577187:	e8 14 47 f8 ff       	call   0x4fb8a0
  57718c:	84 c0                	test   al,al
  57718e:	74 08                	je     0x577198

  57714e:	56                   	push   esi
  57714f:	6a 64                	push   0x64
  577151:	e9 c5 00 00 00       	jmp    0x57721b
  577156:	b9 b4 b0 5d 00       	mov    ecx,0x5db0b4
  57715b:	e8 40 47 f8 ff       	call   0x4fb8a0
  577160:	84 c0                	test   al,al
  577162:	74 08                	je     0x57716c
  577164:	56                   	push   esi
  577165:	6a 26                	push   0x26
  577167:	e9 af 00 00 00       	jmp    0x57721b
  57716c:	b9 c4 b0 5d 00       	mov    ecx,0x5db0c4
  577171:	e8 2a 47 f8 ff       	call   0x4fb8a0
  577176:	84 c0                	test   al,al
  577178:	74 08                	je     0x577182
  57717a:	56                   	push   esi
  57717b:	6a 23                	push   0x23
  57717d:	e9 99 00 00 00       	jmp    0x57721b
  577182:	b9 d8 b0 5d 00       	mov    ecx,0x5db0d8
  577187:	e8 14 47 f8 ff       	call   0x4fb8a0
  57718c:	84 c0                	test   al,al
  57718e:	74 08                	je     0x577198
  577190:	56                   	push   esi
  577191:	6a 28                	push   0x28
  577193:	e9 83 00 00 00       	jmp    0x57721b
  577198:	b9 e8 b0 5d 00       	mov    ecx,0x5db0e8
  57719d:	e8 fe 46 f8 ff       	call   0x4fb8a0
  5771a2:	84 c0                	test   al,al
  5771a4:	74 05                	je     0x5771ab

  577164:	56                   	push   esi
  577165:	6a 26                	push   0x26
  577167:	e9 af 00 00 00       	jmp    0x57721b
  57716c:	b9 c4 b0 5d 00       	mov    ecx,0x5db0c4
  577171:	e8 2a 47 f8 ff       	call   0x4fb8a0
  577176:	84 c0                	test   al,al
  577178:	74 08                	je     0x577182
  57717a:	56                   	push   esi
  57717b:	6a 23                	push   0x23
  57717d:	e9 99 00 00 00       	jmp    0x57721b
  577182:	b9 d8 b0 5d 00       	mov    ecx,0x5db0d8
  577187:	e8 14 47 f8 ff       	call   0x4fb8a0
  57718c:	84 c0                	test   al,al
  57718e:	74 08                	je     0x577198
  577190:	56                   	push   esi
  577191:	6a 28                	push   0x28
  577193:	e9 83 00 00 00       	jmp    0x57721b
  577198:	b9 e8 b0 5d 00       	mov    ecx,0x5db0e8
  57719d:	e8 fe 46 f8 ff       	call   0x4fb8a0
  5771a2:	84 c0                	test   al,al
  5771a4:	74 05                	je     0x5771ab
  5771a6:	56                   	push   esi
  5771a7:	6a 46                	push   0x46
  5771a9:	eb 70                	jmp    0x57721b
  5771ab:	b9 b0 ef 5b 00       	mov    ecx,0x5befb0
  5771b0:	e8 eb 46 f8 ff       	call   0x4fb8a0
  5771b5:	84 c0                	test   al,al
  5771b7:	74 05                	je     0x5771be

  57717a:	56                   	push   esi
  57717b:	6a 23                	push   0x23
  57717d:	e9 99 00 00 00       	jmp    0x57721b
  577182:	b9 d8 b0 5d 00       	mov    ecx,0x5db0d8
  577187:	e8 14 47 f8 ff       	call   0x4fb8a0
  57718c:	84 c0                	test   al,al
  57718e:	74 08                	je     0x577198
  577190:	56                   	push   esi
  577191:	6a 28                	push   0x28
  577193:	e9 83 00 00 00       	jmp    0x57721b
  577198:	b9 e8 b0 5d 00       	mov    ecx,0x5db0e8
  57719d:	e8 fe 46 f8 ff       	call   0x4fb8a0
  5771a2:	84 c0                	test   al,al
  5771a4:	74 05                	je     0x5771ab
  5771a6:	56                   	push   esi
  5771a7:	6a 46                	push   0x46
  5771a9:	eb 70                	jmp    0x57721b
  5771ab:	b9 b0 ef 5b 00       	mov    ecx,0x5befb0
  5771b0:	e8 eb 46 f8 ff       	call   0x4fb8a0
  5771b5:	84 c0                	test   al,al
  5771b7:	74 05                	je     0x5771be
  5771b9:	56                   	push   esi
  5771ba:	6a 0f                	push   0xf
  5771bc:	eb 5d                	jmp    0x57721b
  5771be:	b9 fc b0 5d 00       	mov    ecx,0x5db0fc
  5771c3:	e8 d8 46 f8 ff       	call   0x4fb8a0
  5771c8:	84 c0                	test   al,al
  5771ca:	74 05                	je     0x5771d1

  577190:	56                   	push   esi
  577191:	6a 28                	push   0x28
  577193:	e9 83 00 00 00       	jmp    0x57721b
  577198:	b9 e8 b0 5d 00       	mov    ecx,0x5db0e8
  57719d:	e8 fe 46 f8 ff       	call   0x4fb8a0
  5771a2:	84 c0                	test   al,al
  5771a4:	74 05                	je     0x5771ab
  5771a6:	56                   	push   esi
  5771a7:	6a 46                	push   0x46
  5771a9:	eb 70                	jmp    0x57721b
  5771ab:	b9 b0 ef 5b 00       	mov    ecx,0x5befb0
  5771b0:	e8 eb 46 f8 ff       	call   0x4fb8a0
  5771b5:	84 c0                	test   al,al
  5771b7:	74 05                	je     0x5771be
  5771b9:	56                   	push   esi
  5771ba:	6a 0f                	push   0xf
  5771bc:	eb 5d                	jmp    0x57721b
  5771be:	b9 fc b0 5d 00       	mov    ecx,0x5db0fc
  5771c3:	e8 d8 46 f8 ff       	call   0x4fb8a0
  5771c8:	84 c0                	test   al,al
  5771ca:	74 05                	je     0x5771d1
  5771cc:	56                   	push   esi
  5771cd:	6a 03                	push   0x3
  5771cf:	eb 4a                	jmp    0x57721b
  5771d1:	b9 08 b4 5c 00       	mov    ecx,0x5cb408
  5771d6:	e8 c5 46 f8 ff       	call   0x4fb8a0
  5771db:	84 c0                	test   al,al
  5771dd:	74 05                	je     0x5771e4

  5771a6:	56                   	push   esi
  5771a7:	6a 46                	push   0x46
  5771a9:	eb 70                	jmp    0x57721b
  5771ab:	b9 b0 ef 5b 00       	mov    ecx,0x5befb0
  5771b0:	e8 eb 46 f8 ff       	call   0x4fb8a0
  5771b5:	84 c0                	test   al,al
  5771b7:	74 05                	je     0x5771be
  5771b9:	56                   	push   esi
  5771ba:	6a 0f                	push   0xf
  5771bc:	eb 5d                	jmp    0x57721b
  5771be:	b9 fc b0 5d 00       	mov    ecx,0x5db0fc
  5771c3:	e8 d8 46 f8 ff       	call   0x4fb8a0
  5771c8:	84 c0                	test   al,al
  5771ca:	74 05                	je     0x5771d1
  5771cc:	56                   	push   esi
  5771cd:	6a 03                	push   0x3
  5771cf:	eb 4a                	jmp    0x57721b
  5771d1:	b9 08 b4 5c 00       	mov    ecx,0x5cb408
  5771d6:	e8 c5 46 f8 ff       	call   0x4fb8a0
  5771db:	84 c0                	test   al,al
  5771dd:	74 05                	je     0x5771e4
  5771df:	56                   	push   esi
  5771e0:	6a 0a                	push   0xa
  5771e2:	eb 37                	jmp    0x57721b
  5771e4:	b9 08 b1 5d 00       	mov    ecx,0x5db108
  5771e9:	e8 b2 46 f8 ff       	call   0x4fb8a0
  5771ee:	84 c0                	test   al,al
  5771f0:	74 05                	je     0x5771f7

  5771b9:	56                   	push   esi
  5771ba:	6a 0f                	push   0xf
  5771bc:	eb 5d                	jmp    0x57721b
  5771be:	b9 fc b0 5d 00       	mov    ecx,0x5db0fc
  5771c3:	e8 d8 46 f8 ff       	call   0x4fb8a0
  5771c8:	84 c0                	test   al,al
  5771ca:	74 05                	je     0x5771d1
  5771cc:	56                   	push   esi
  5771cd:	6a 03                	push   0x3
  5771cf:	eb 4a                	jmp    0x57721b
  5771d1:	b9 08 b4 5c 00       	mov    ecx,0x5cb408
  5771d6:	e8 c5 46 f8 ff       	call   0x4fb8a0
  5771db:	84 c0                	test   al,al
  5771dd:	74 05                	je     0x5771e4
  5771df:	56                   	push   esi
  5771e0:	6a 0a                	push   0xa
  5771e2:	eb 37                	jmp    0x57721b
  5771e4:	b9 08 b1 5d 00       	mov    ecx,0x5db108
  5771e9:	e8 b2 46 f8 ff       	call   0x4fb8a0
  5771ee:	84 c0                	test   al,al
  5771f0:	74 05                	je     0x5771f7
  5771f2:	56                   	push   esi
  5771f3:	6a 05                	push   0x5
  5771f5:	eb 24                	jmp    0x57721b
  5771f7:	b9 1c b1 5d 00       	mov    ecx,0x5db11c
  5771fc:	e8 9f 46 f8 ff       	call   0x4fb8a0
  577201:	84 c0                	test   al,al
  577203:	74 05                	je     0x57720a

  5771cc:	56                   	push   esi
  5771cd:	6a 03                	push   0x3
  5771cf:	eb 4a                	jmp    0x57721b
  5771d1:	b9 08 b4 5c 00       	mov    ecx,0x5cb408
  5771d6:	e8 c5 46 f8 ff       	call   0x4fb8a0
  5771db:	84 c0                	test   al,al
  5771dd:	74 05                	je     0x5771e4
  5771df:	56                   	push   esi
  5771e0:	6a 0a                	push   0xa
  5771e2:	eb 37                	jmp    0x57721b
  5771e4:	b9 08 b1 5d 00       	mov    ecx,0x5db108
  5771e9:	e8 b2 46 f8 ff       	call   0x4fb8a0
  5771ee:	84 c0                	test   al,al
  5771f0:	74 05                	je     0x5771f7
  5771f2:	56                   	push   esi
  5771f3:	6a 05                	push   0x5
  5771f5:	eb 24                	jmp    0x57721b
  5771f7:	b9 1c b1 5d 00       	mov    ecx,0x5db11c
  5771fc:	e8 9f 46 f8 ff       	call   0x4fb8a0
  577201:	84 c0                	test   al,al
  577203:	74 05                	je     0x57720a
  577205:	56                   	push   esi
  577206:	6a 1e                	push   0x1e
  577208:	eb 11                	jmp    0x57721b
  57720a:	b9 30 b1 5d 00       	mov    ecx,0x5db130
  57720f:	e8 8c 46 f8 ff       	call   0x4fb8a0
  577214:	84 c0                	test   al,al
  577216:	74 79                	je     0x577291

  5771df:	56                   	push   esi
  5771e0:	6a 0a                	push   0xa
  5771e2:	eb 37                	jmp    0x57721b
  5771e4:	b9 08 b1 5d 00       	mov    ecx,0x5db108
  5771e9:	e8 b2 46 f8 ff       	call   0x4fb8a0
  5771ee:	84 c0                	test   al,al
  5771f0:	74 05                	je     0x5771f7
  5771f2:	56                   	push   esi
  5771f3:	6a 05                	push   0x5
  5771f5:	eb 24                	jmp    0x57721b
  5771f7:	b9 1c b1 5d 00       	mov    ecx,0x5db11c
  5771fc:	e8 9f 46 f8 ff       	call   0x4fb8a0
  577201:	84 c0                	test   al,al
  577203:	74 05                	je     0x57720a
  577205:	56                   	push   esi
  577206:	6a 1e                	push   0x1e
  577208:	eb 11                	jmp    0x57721b
  57720a:	b9 30 b1 5d 00       	mov    ecx,0x5db130
  57720f:	e8 8c 46 f8 ff       	call   0x4fb8a0
  577214:	84 c0                	test   al,al
  577216:	74 79                	je     0x577291
  577218:	56                   	push   esi
  577219:	6a 14                	push   0x14
  57721b:	8d 84 24 30 0b 02 00 	lea    eax,[esp+0x20b30]
  577222:	68 38 b0 5d 00       	push   0x5db038
  577227:	50                   	push   eax
  577228:	e8 a3 9e e8 ff       	call   0x4010d0
  57722d:	83 c4 10             	add    esp,0x10

  57c7f1:	8b 0c b5 d0 ac 72 0a 	mov    ecx,DWORD PTR [esi*4+0xa72acd0]
  57c7f8:	81 e9 50 c3 00 00    	sub    ecx,0xc350
  57c7fe:	69 c9 ac 00 00 00    	imul   ecx,ecx,0xac
  57c804:	8d 91 a8 16 92 05    	lea    edx,[ecx+0x59216a8]
  57c80a:	8b c8                	mov    ecx,eax
  57c80c:	e8 2f 45 f4 ff       	call   0x4c0d40
  57c811:	80 8a a5 00 00 00 80 	or     BYTE PTR [edx+0xa5],0x80
  57c818:	eb 04                	jmp    0x57c81e
  57c81a:	8b 74 24 14          	mov    esi,DWORD PTR [esp+0x14]
  57c81e:	b9 7c c1 5d 00       	mov    ecx,0x5dc17c
  57c823:	e8 78 f0 f7 ff       	call   0x4fb8a0
  57c828:	84 c0                	test   al,al
  57c82a:	74 19                	je     0x57c845
  57c82c:	8b 04 b5 d0 ac 72 0a 	mov    eax,DWORD PTR [esi*4+0xa72acd0]
  57c833:	2d 50 c3 00 00       	sub    eax,0xc350
  57c838:	69 c0 ac 00 00 00    	imul   eax,eax,0xac
  57c83e:	c6 80 3b 17 92 05 01 	mov    BYTE PTR [eax+0x592173b],0x1
  57c845:	b9 88 c1 5d 00       	mov    ecx,0x5dc188
  57c84a:	e8 51 f0 f7 ff       	call   0x4fb8a0
  57c84f:	84 c0                	test   al,al
  57c851:	0f 84 e8 00 00 00    	je     0x57c93f
  57c857:	68 44 05 59 00       	push   0x590544
  57c85c:	68 89 52 91 05       	push   0x5915289
  57c861:	ff 15 50 c3 58 00    	call   DWORD PTR ds:0x58c350
  57c867:	83 c4 08             	add    esp,0x8
  57c86a:	8b d7                	mov    edx,edi
  57c86c:	8b ce                	mov    ecx,esi
  57c86e:	85 c0                	test   eax,eax

  579432:	50                   	push   eax
  579433:	8d 84 24 50 0b 02 00 	lea    eax,[esp+0x20b50]
  57943a:	68 34 b5 5d 00       	push   0x5db534
  57943f:	50                   	push   eax
  579440:	e8 8b 7c e8 ff       	call   0x4010d0
  579445:	8d 8c 24 58 0b 02 00 	lea    ecx,[esp+0x20b58]
  57944c:	e8 bf d0 f7 ff       	call   0x4f6510
  579451:	0f b6 05 4e 44 62 0a 	movzx  eax,BYTE PTR ds:0xa62444e
  579458:	68 50 44 62 0a       	push   0xa624450
  57945d:	50                   	push   eax
  57945e:	8d 84 24 60 0b 02 00 	lea    eax,[esp+0x20b60]
  579465:	68 44 b5 5d 00       	push   0x5db544
  57946a:	50                   	push   eax
  57946b:	e8 60 7c e8 ff       	call   0x4010d0
  579470:	83 c4 40             	add    esp,0x40
  579473:	8d 8c 24 28 0b 02 00 	lea    ecx,[esp+0x20b28]
  57947a:	e8 91 d0 f7 ff       	call   0x4f6510
  57947f:	b9 50 b5 5d 00       	mov    ecx,0x5db550
  579484:	e8 17 24 f8 ff       	call   0x4fb8a0
  579489:	84 c0                	test   al,al
  57948b:	74 0d                	je     0x57949a
  57948d:	a1 c4 b1 72 0a       	mov    eax,ds:0xa72b1c4
  579492:	40                   	inc    eax
  579493:	a3 b4 1a 18 02       	mov    ds:0x2181ab4,eax
  579498:	eb 0a                	jmp    0x5794a4
  57949a:	c7 05 b4 1a 18 02 00 	mov    DWORD PTR ds:0x2181ab4,0x0
  5794a1:	00 00 00 
  5794a4:	b9 5c b5 5d 00       	mov    ecx,0x5db55c

  57945e:	8d 84 24 60 0b 02 00 	lea    eax,[esp+0x20b60]
  579465:	68 44 b5 5d 00       	push   0x5db544
  57946a:	50                   	push   eax
  57946b:	e8 60 7c e8 ff       	call   0x4010d0
  579470:	83 c4 40             	add    esp,0x40
  579473:	8d 8c 24 28 0b 02 00 	lea    ecx,[esp+0x20b28]
  57947a:	e8 91 d0 f7 ff       	call   0x4f6510
  57947f:	b9 50 b5 5d 00       	mov    ecx,0x5db550
  579484:	e8 17 24 f8 ff       	call   0x4fb8a0
  579489:	84 c0                	test   al,al
  57948b:	74 0d                	je     0x57949a
  57948d:	a1 c4 b1 72 0a       	mov    eax,ds:0xa72b1c4
  579492:	40                   	inc    eax
  579493:	a3 b4 1a 18 02       	mov    ds:0x2181ab4,eax
  579498:	eb 0a                	jmp    0x5794a4
  57949a:	c7 05 b4 1a 18 02 00 	mov    DWORD PTR ds:0x2181ab4,0x0
  5794a1:	00 00 00 
  5794a4:	b9 5c b5 5d 00       	mov    ecx,0x5db55c
  5794a9:	e8 f2 23 f8 ff       	call   0x4fb8a0
  5794ae:	84 c0                	test   al,al
  5794b0:	74 32                	je     0x5794e4
  5794b2:	f3 0f 10 05 80 1c 18 	movss  xmm0,DWORD PTR ds:0x2181c80
  5794b9:	02 
  5794ba:	f3 0f 58 05 4c d5 5d 	addss  xmm0,DWORD PTR ds:0x5dd54c
  5794c1:	00 
  5794c2:	f3 0f 11 05 80 1c 18 	movss  DWORD PTR ds:0x2181c80,xmm0
  5794c9:	02 
  5794ca:	f3 0f 10 05 7c 1c 18 	movss  xmm0,DWORD PTR ds:0x2181c7c

  5794a4:	b9 5c b5 5d 00       	mov    ecx,0x5db55c
  5794a9:	e8 f2 23 f8 ff       	call   0x4fb8a0
  5794ae:	84 c0                	test   al,al
  5794b0:	74 32                	je     0x5794e4
  5794b2:	f3 0f 10 05 80 1c 18 	movss  xmm0,DWORD PTR ds:0x2181c80
  5794b9:	02 
  5794ba:	f3 0f 58 05 4c d5 5d 	addss  xmm0,DWORD PTR ds:0x5dd54c
  5794c1:	00 
  5794c2:	f3 0f 11 05 80 1c 18 	movss  DWORD PTR ds:0x2181c80,xmm0
  5794c9:	02 
  5794ca:	f3 0f 10 05 7c 1c 18 	movss  xmm0,DWORD PTR ds:0x2181c7c
  5794d1:	02 
  5794d2:	f3 0f 58 05 4c d5 5d 	addss  xmm0,DWORD PTR ds:0x5dd54c
  5794d9:	00 
  5794da:	f3 0f 11 05 7c 1c 18 	movss  DWORD PTR ds:0x2181c7c,xmm0
  5794e1:	02 
  5794e2:	eb 22                	jmp    0x579506
  5794e4:	b9 64 b5 5d 00       	mov    ecx,0x5db564
  5794e9:	e8 b2 23 f8 ff       	call   0x4fb8a0
  5794ee:	84 c0                	test   al,al
  5794f0:	74 2c                	je     0x57951e
  5794f2:	c7 05 80 1c 18 02 00 	mov    DWORD PTR ds:0x2181c80,0x0
  5794f9:	00 00 00 
  5794fc:	c7 05 7c 1c 18 02 00 	mov    DWORD PTR ds:0x2181c7c,0x0
  579503:	00 00 00 
  579506:	8b 0d 1c 2c 5e 00    	mov    ecx,DWORD PTR ds:0x5e2c1c
  57950c:	81 f9 18 fc ff ff    	cmp    ecx,0xfffffc18
  579512:	74 0a                	je     0x57951e

  5794d9:	00 
  5794da:	f3 0f 11 05 7c 1c 18 	movss  DWORD PTR ds:0x2181c7c,xmm0
  5794e1:	02 
  5794e2:	eb 22                	jmp    0x579506
  5794e4:	b9 64 b5 5d 00       	mov    ecx,0x5db564
  5794e9:	e8 b2 23 f8 ff       	call   0x4fb8a0
  5794ee:	84 c0                	test   al,al
  5794f0:	74 2c                	je     0x57951e
  5794f2:	c7 05 80 1c 18 02 00 	mov    DWORD PTR ds:0x2181c80,0x0
  5794f9:	00 00 00 
  5794fc:	c7 05 7c 1c 18 02 00 	mov    DWORD PTR ds:0x2181c7c,0x0
  579503:	00 00 00 
  579506:	8b 0d 1c 2c 5e 00    	mov    ecx,DWORD PTR ds:0x5e2c1c
  57950c:	81 f9 18 fc ff ff    	cmp    ecx,0xfffffc18
  579512:	74 0a                	je     0x57951e
  579514:	ba 58 f5 17 02       	mov    edx,0x217f558
  579519:	e8 42 1c f1 ff       	call   0x48b160
  57951e:	b9 74 b5 5d 00       	mov    ecx,0x5db574
  579523:	e8 78 23 f8 ff       	call   0x4fb8a0
  579528:	84 c0                	test   al,al
  57952a:	74 58                	je     0x579584
  57952c:	e8 2f 2c f1 ff       	call   0x48c160
  579531:	85 c0                	test   eax,eax
  579533:	74 08                	je     0x57953d
  579535:	8b 35 40 bd 72 0a    	mov    esi,DWORD PTR ds:0xa72bd40
  57953b:	eb 13                	jmp    0x579550
  57953d:	8b 0d 40 bd 72 0a    	mov    ecx,DWORD PTR ds:0xa72bd40
  579543:	e8 78 26 f7 ff       	call   0x4ebbc0

  57954a:	03 35 e8 b8 72 0a    	add    esi,DWORD PTR ds:0xa72b8e8
  579550:	e8 0b 2c f1 ff       	call   0x48c160
  579555:	85 c0                	test   eax,eax
  579557:	74 07                	je     0x579560
  579559:	a1 9c 1c 6d 0a       	mov    eax,ds:0xa6d1c9c
  57955e:	eb 11                	jmp    0x579571
  579560:	8b 0d 9c 1c 6d 0a    	mov    ecx,DWORD PTR ds:0xa6d1c9c
  579566:	e8 55 26 f7 ff       	call   0x4ebbc0
  57956b:	03 05 e4 b8 72 0a    	add    eax,DWORD PTR ds:0xa72b8e4
  579571:	56                   	push   esi
  579572:	8b 74 24 18          	mov    esi,DWORD PTR [esp+0x18]
  579576:	8b d0                	mov    edx,eax
  579578:	8b ce                	mov    ecx,esi
  57957a:	e8 31 71 f0 ff       	call   0x4806b0
  57957f:	83 c4 04             	add    esp,0x4
  579582:	eb 04                	jmp    0x579588
  579584:	8b 74 24 14          	mov    esi,DWORD PTR [esp+0x14]
  579588:	b9 80 b5 5d 00       	mov    ecx,0x5db580
  57958d:	e8 0e 23 f8 ff       	call   0x4fb8a0
  579592:	84 c0                	test   al,al
  579594:	74 07                	je     0x57959d
  579596:	8b ce                	mov    ecx,esi
  579598:	e8 83 17 f1 ff       	call   0x48ad20
  57959d:	8b 3d 50 c3 58 00    	mov    edi,DWORD PTR ds:0x58c350
  5795a3:	8d 84 24 28 0b 02 00 	lea    eax,[esp+0x20b28]
  5795aa:	68 90 b5 5d 00       	push   0x5db590
  5795af:	50                   	push   eax
  5795b0:	ff d7                	call   edi

  579eaf:	33 d2                	xor    edx,edx
  579eb1:	8b cf                	mov    ecx,edi
  579eb3:	89 7c 24 20          	mov    DWORD PTR [esp+0x20],edi
  579eb7:	e8 f4 90 fb ff       	call   0x532fb0
  579ebc:	0f b6 c0             	movzx  eax,al
  579ebf:	50                   	push   eax
  579ec0:	8d 84 24 2c 0b 02 00 	lea    eax,[esp+0x20b2c]
  579ec7:	68 38 b7 5d 00       	push   0x5db738
  579ecc:	50                   	push   eax
  579ecd:	e8 fe 71 e8 ff       	call   0x4010d0
  579ed2:	83 c4 0c             	add    esp,0xc
  579ed5:	8d 8c 24 28 0b 02 00 	lea    ecx,[esp+0x20b28]
  579edc:	e8 2f c6 f7 ff       	call   0x4f6510
  579ee1:	8b cf                	mov    ecx,edi
  579ee3:	e8 08 0f f3 ff       	call   0x4aadf0
  579ee8:	84 c0                	test   al,al
  579eea:	0f 84 a4 00 00 00    	je     0x579f94
  579ef0:	b9 54 b7 5d 00       	mov    ecx,0x5db754
  579ef5:	e8 a6 19 f8 ff       	call   0x4fb8a0
  579efa:	84 c0                	test   al,al
  579efc:	0f 84 cb 00 00 00    	je     0x579fcd
  579f02:	69 c7 68 05 00 00    	imul   eax,edi,0x568
  579f08:	c7 44 24 14 00 00 00 	mov    DWORD PTR [esp+0x14],0x0
  579f0f:	00 
  579f10:	89 44 24 18          	mov    DWORD PTR [esp+0x18],eax
  579f14:	c7 80 bc 14 15 06 45 	mov    DWORD PTR [eax+0x61514bc],0x245
  579f1b:	02 00 00 
  579f1e:	ff 15 1c c5 58 00    	call   DWORD PTR ds:0x58c51c

  579f55:	80 c2 3c             	add    dl,0x3c
  579f58:	88 91 42 14 15 06    	mov    BYTE PTR [ecx+0x6151442],dl
  579f5e:	0f b6 81 88 14 15 06 	movzx  eax,BYTE PTR [ecx+0x6151488]
  579f65:	ff 34 85 8c e3 58 00 	push   DWORD PTR [eax*4+0x58e38c]
  579f6c:	8d 81 08 14 15 06    	lea    eax,[ecx+0x6151408]
  579f72:	68 a0 49 5a 00       	push   0x5a49a0
  579f77:	50                   	push   eax
  579f78:	e8 53 71 e8 ff       	call   0x4010d0
  579f7d:	83 c4 0c             	add    esp,0xc
  579f80:	5f                   	pop    edi
  579f81:	5e                   	pop    esi
  579f82:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  579f89:	33 cc                	xor    ecx,esp
  579f8b:	e8 1e 01 01 00       	call   0x58a0ae
  579f90:	8b e5                	mov    esp,ebp
  579f92:	5d                   	pop    ebp
  579f93:	c3                   	ret
  579f94:	b9 64 b7 5d 00       	mov    ecx,0x5db764
  579f99:	e8 02 19 f8 ff       	call   0x4fb8a0
  579f9e:	84 c0                	test   al,al
  579fa0:	74 2b                	je     0x579fcd
  579fa2:	8b 15 3c bd 72 0a    	mov    edx,DWORD PTR ds:0xa72bd3c
  579fa8:	51                   	push   ecx
  579fa9:	ff 35 34 1c 6d 0a    	push   DWORD PTR ds:0xa6d1c34
  579faf:	8b cf                	mov    ecx,edi
  579fb1:	e8 aa 2a ea ff       	call   0x41ca60
  579fb6:	83 c4 08             	add    esp,0x8
  579fb9:	5f                   	pop    edi

  579f99:	e8 02 19 f8 ff       	call   0x4fb8a0
  579f9e:	84 c0                	test   al,al
  579fa0:	74 2b                	je     0x579fcd
  579fa2:	8b 15 3c bd 72 0a    	mov    edx,DWORD PTR ds:0xa72bd3c
  579fa8:	51                   	push   ecx
  579fa9:	ff 35 34 1c 6d 0a    	push   DWORD PTR ds:0xa6d1c34
  579faf:	8b cf                	mov    ecx,edi
  579fb1:	e8 aa 2a ea ff       	call   0x41ca60
  579fb6:	83 c4 08             	add    esp,0x8
  579fb9:	5f                   	pop    edi
  579fba:	5e                   	pop    esi
  579fbb:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  579fc2:	33 cc                	xor    ecx,esp
  579fc4:	e8 e5 00 01 00       	call   0x58a0ae
  579fc9:	8b e5                	mov    esp,ebp
  579fcb:	5d                   	pop    ebp
  579fcc:	c3                   	ret
  579fcd:	b9 6c b7 5d 00       	mov    ecx,0x5db76c
  579fd2:	e8 c9 18 f8 ff       	call   0x4fb8a0
  579fd7:	84 c0                	test   al,al
  579fd9:	74 07                	je     0x579fe2
  579fdb:	8b cf                	mov    ecx,edi
  579fdd:	e8 fe d3 f0 ff       	call   0x4873e0
  579fe2:	b9 74 b7 5d 00       	mov    ecx,0x5db774
  579fe7:	e8 b4 18 f8 ff       	call   0x4fb8a0
  579fec:	84 c0                	test   al,al
  579fee:	74 07                	je     0x579ff7
  579ff0:	8b cf                	mov    ecx,edi

  579faf:	8b cf                	mov    ecx,edi
  579fb1:	e8 aa 2a ea ff       	call   0x41ca60
  579fb6:	83 c4 08             	add    esp,0x8
  579fb9:	5f                   	pop    edi
  579fba:	5e                   	pop    esi
  579fbb:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  579fc2:	33 cc                	xor    ecx,esp
  579fc4:	e8 e5 00 01 00       	call   0x58a0ae
  579fc9:	8b e5                	mov    esp,ebp
  579fcb:	5d                   	pop    ebp
  579fcc:	c3                   	ret
  579fcd:	b9 6c b7 5d 00       	mov    ecx,0x5db76c
  579fd2:	e8 c9 18 f8 ff       	call   0x4fb8a0
  579fd7:	84 c0                	test   al,al
  579fd9:	74 07                	je     0x579fe2
  579fdb:	8b cf                	mov    ecx,edi
  579fdd:	e8 fe d3 f0 ff       	call   0x4873e0
  579fe2:	b9 74 b7 5d 00       	mov    ecx,0x5db774
  579fe7:	e8 b4 18 f8 ff       	call   0x4fb8a0
  579fec:	84 c0                	test   al,al
  579fee:	74 07                	je     0x579ff7
  579ff0:	8b cf                	mov    ecx,edi
  579ff2:	e8 a9 d4 f0 ff       	call   0x4874a0
  579ff7:	b9 84 b7 5d 00       	mov    ecx,0x5db784
  579ffc:	e8 9f 18 f8 ff       	call   0x4fb8a0
  57a001:	84 c0                	test   al,al
  57a003:	74 07                	je     0x57a00c
  57a005:	8b cf                	mov    ecx,edi

  579fc2:	33 cc                	xor    ecx,esp
  579fc4:	e8 e5 00 01 00       	call   0x58a0ae
  579fc9:	8b e5                	mov    esp,ebp
  579fcb:	5d                   	pop    ebp
  579fcc:	c3                   	ret
  579fcd:	b9 6c b7 5d 00       	mov    ecx,0x5db76c
  579fd2:	e8 c9 18 f8 ff       	call   0x4fb8a0
  579fd7:	84 c0                	test   al,al
  579fd9:	74 07                	je     0x579fe2
  579fdb:	8b cf                	mov    ecx,edi
  579fdd:	e8 fe d3 f0 ff       	call   0x4873e0
  579fe2:	b9 74 b7 5d 00       	mov    ecx,0x5db774
  579fe7:	e8 b4 18 f8 ff       	call   0x4fb8a0
  579fec:	84 c0                	test   al,al
  579fee:	74 07                	je     0x579ff7
  579ff0:	8b cf                	mov    ecx,edi
  579ff2:	e8 a9 d4 f0 ff       	call   0x4874a0
  579ff7:	b9 84 b7 5d 00       	mov    ecx,0x5db784
  579ffc:	e8 9f 18 f8 ff       	call   0x4fb8a0
  57a001:	84 c0                	test   al,al
  57a003:	74 07                	je     0x57a00c
  57a005:	8b cf                	mov    ecx,edi
  57a007:	e8 d4 f0 ea ff       	call   0x4290e0
  57a00c:	b9 90 b7 5d 00       	mov    ecx,0x5db790
  57a011:	e8 8a 18 f8 ff       	call   0x4fb8a0
  57a016:	84 c0                	test   al,al
  57a018:	74 71                	je     0x57a08b
  57a01a:	c7 44 24 14 00 00 00 	mov    DWORD PTR [esp+0x14],0x0

  579fd2:	e8 c9 18 f8 ff       	call   0x4fb8a0
  579fd7:	84 c0                	test   al,al
  579fd9:	74 07                	je     0x579fe2
  579fdb:	8b cf                	mov    ecx,edi
  579fdd:	e8 fe d3 f0 ff       	call   0x4873e0
  579fe2:	b9 74 b7 5d 00       	mov    ecx,0x5db774
  579fe7:	e8 b4 18 f8 ff       	call   0x4fb8a0
  579fec:	84 c0                	test   al,al
  579fee:	74 07                	je     0x579ff7
  579ff0:	8b cf                	mov    ecx,edi
  579ff2:	e8 a9 d4 f0 ff       	call   0x4874a0
  579ff7:	b9 84 b7 5d 00       	mov    ecx,0x5db784
  579ffc:	e8 9f 18 f8 ff       	call   0x4fb8a0
  57a001:	84 c0                	test   al,al
  57a003:	74 07                	je     0x57a00c
  57a005:	8b cf                	mov    ecx,edi
  57a007:	e8 d4 f0 ea ff       	call   0x4290e0
  57a00c:	b9 90 b7 5d 00       	mov    ecx,0x5db790
  57a011:	e8 8a 18 f8 ff       	call   0x4fb8a0
  57a016:	84 c0                	test   al,al
  57a018:	74 71                	je     0x57a08b
  57a01a:	c7 44 24 14 00 00 00 	mov    DWORD PTR [esp+0x14],0x0
  57a021:	00 
  57a022:	ff 15 1c c5 58 00    	call   DWORD PTR ds:0x58c51c
  57a028:	8b f8                	mov    edi,eax
  57a02a:	81 e7 01 00 00 80    	and    edi,0x80000001
  57a030:	79 05                	jns    0x57a037
  57a032:	4f                   	dec    edi

  57a05a:	74 db                	je     0x57a037
  57a05c:	8b 4c 24 20          	mov    ecx,DWORD PTR [esp+0x20]
  57a060:	ba 03 00 00 00       	mov    edx,0x3
  57a065:	68 17 fc ff ff       	push   0xfffffc17
  57a06a:	50                   	push   eax
  57a06b:	6a 0d                	push   0xd
  57a06d:	6a 12                	push   0x12
  57a06f:	e8 fc ec fa ff       	call   0x528d70
  57a074:	83 c4 10             	add    esp,0x10
  57a077:	5f                   	pop    edi
  57a078:	5e                   	pop    esi
  57a079:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  57a080:	33 cc                	xor    ecx,esp
  57a082:	e8 27 00 01 00       	call   0x58a0ae
  57a087:	8b e5                	mov    esp,ebp
  57a089:	5d                   	pop    ebp
  57a08a:	c3                   	ret
  57a08b:	b9 a0 b7 5d 00       	mov    ecx,0x5db7a0
  57a090:	e8 0b 18 f8 ff       	call   0x4fb8a0
  57a095:	84 c0                	test   al,al
  57a097:	74 67                	je     0x57a100
  57a099:	33 d2                	xor    edx,edx
  57a09b:	8b cf                	mov    ecx,edi
  57a09d:	e8 ee 0f f3 ff       	call   0x4ab090
  57a0a2:	69 f7 68 05 00 00    	imul   esi,edi,0x568
  57a0a8:	8b cf                	mov    ecx,edi
  57a0aa:	c7 86 5c 19 15 06 00 	mov    DWORD PTR [esi+0x615195c],0x42480000
  57a0b1:	00 48 42 

  57a0c7:	06 
  57a0c8:	8b 86 e4 15 15 06    	mov    eax,DWORD PTR [esi+0x61515e4]
  57a0ce:	a9 00 01 00 00       	test   eax,0x100
  57a0d3:	75 05                	jne    0x57a0da
  57a0d5:	05 00 01 00 00       	add    eax,0x100
  57a0da:	ba 01 00 00 00       	mov    edx,0x1
  57a0df:	89 86 e4 15 15 06    	mov    DWORD PTR [esi+0x61515e4],eax
  57a0e5:	8b cf                	mov    ecx,edi
  57a0e7:	e8 a4 0f f3 ff       	call   0x4ab090
  57a0ec:	5f                   	pop    edi
  57a0ed:	5e                   	pop    esi
  57a0ee:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  57a0f5:	33 cc                	xor    ecx,esp
  57a0f7:	e8 b2 ff 00 00       	call   0x58a0ae
  57a0fc:	8b e5                	mov    esp,ebp
  57a0fe:	5d                   	pop    ebp
  57a0ff:	c3                   	ret
  57a100:	b9 b0 b7 5d 00       	mov    ecx,0x5db7b0
  57a105:	e8 96 17 f8 ff       	call   0x4fb8a0
  57a10a:	84 c0                	test   al,al
  57a10c:	74 20                	je     0x57a12e
  57a10e:	6a 00                	push   0x0
  57a110:	8b d7                	mov    edx,edi
  57a112:	e8 29 25 ea ff       	call   0x41c640
  57a117:	83 c4 04             	add    esp,0x4
  57a11a:	5f                   	pop    edi
  57a11b:	5e                   	pop    esi
  57a11c:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]

  57a0ff:	c3                   	ret
  57a100:	b9 b0 b7 5d 00       	mov    ecx,0x5db7b0
  57a105:	e8 96 17 f8 ff       	call   0x4fb8a0
  57a10a:	84 c0                	test   al,al
  57a10c:	74 20                	je     0x57a12e
  57a10e:	6a 00                	push   0x0
  57a110:	8b d7                	mov    edx,edi
  57a112:	e8 29 25 ea ff       	call   0x41c640
  57a117:	83 c4 04             	add    esp,0x4
  57a11a:	5f                   	pop    edi
  57a11b:	5e                   	pop    esi
  57a11c:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  57a123:	33 cc                	xor    ecx,esp
  57a125:	e8 84 ff 00 00       	call   0x58a0ae
  57a12a:	8b e5                	mov    esp,ebp
  57a12c:	5d                   	pop    ebp
  57a12d:	c3                   	ret
  57a12e:	b9 bc b7 5d 00       	mov    ecx,0x5db7bc
  57a133:	e8 68 17 f8 ff       	call   0x4fb8a0
  57a138:	84 c0                	test   al,al
  57a13a:	74 1d                	je     0x57a159
  57a13c:	8b d6                	mov    edx,esi
  57a13e:	8b cf                	mov    ecx,edi
  57a140:	e8 6b 60 ea ff       	call   0x4201b0
  57a145:	68 96 00 00 00       	push   0x96
  57a14a:	ba 6f 00 00 00       	mov    edx,0x6f
  57a14f:	8b cf                	mov    ecx,edi
  57a151:	e8 ca a5 ea ff       	call   0x424720

  57a123:	33 cc                	xor    ecx,esp
  57a125:	e8 84 ff 00 00       	call   0x58a0ae
  57a12a:	8b e5                	mov    esp,ebp
  57a12c:	5d                   	pop    ebp
  57a12d:	c3                   	ret
  57a12e:	b9 bc b7 5d 00       	mov    ecx,0x5db7bc
  57a133:	e8 68 17 f8 ff       	call   0x4fb8a0
  57a138:	84 c0                	test   al,al
  57a13a:	74 1d                	je     0x57a159
  57a13c:	8b d6                	mov    edx,esi
  57a13e:	8b cf                	mov    ecx,edi
  57a140:	e8 6b 60 ea ff       	call   0x4201b0
  57a145:	68 96 00 00 00       	push   0x96
  57a14a:	ba 6f 00 00 00       	mov    edx,0x6f
  57a14f:	8b cf                	mov    ecx,edi
  57a151:	e8 ca a5 ea ff       	call   0x424720
  57a156:	83 c4 04             	add    esp,0x4
  57a159:	b9 c8 b7 5d 00       	mov    ecx,0x5db7c8
  57a15e:	e8 3d 17 f8 ff       	call   0x4fb8a0
  57a163:	84 c0                	test   al,al
  57a165:	74 41                	je     0x57a1a8
  57a167:	8b d6                	mov    edx,esi
  57a169:	8b cf                	mov    ecx,edi
  57a16b:	e8 40 60 ea ff       	call   0x4201b0
  57a170:	69 c7 68 05 00 00    	imul   eax,edi,0x568
  57a176:	33 c9                	xor    ecx,ecx
  57a178:	6a 01                	push   0x1
  57a17a:	66 89 88 98 14 15 06 	mov    WORD PTR [eax+0x6151498],cx

  57a176:	33 c9                	xor    ecx,ecx
  57a178:	6a 01                	push   0x1
  57a17a:	66 89 88 98 14 15 06 	mov    WORD PTR [eax+0x6151498],cx
  57a181:	8b cf                	mov    ecx,edi
  57a183:	e8 38 f0 e9 ff       	call   0x4191c0
  57a188:	8b d0                	mov    edx,eax
  57a18a:	8b cf                	mov    ecx,edi
  57a18c:	e8 5f 9c ea ff       	call   0x423df0
  57a191:	83 c4 04             	add    esp,0x4
  57a194:	5f                   	pop    edi
  57a195:	5e                   	pop    esi
  57a196:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  57a19d:	33 cc                	xor    ecx,esp
  57a19f:	e8 0a ff 00 00       	call   0x58a0ae
  57a1a4:	8b e5                	mov    esp,ebp
  57a1a6:	5d                   	pop    ebp
  57a1a7:	c3                   	ret
  57a1a8:	b9 d4 b7 5d 00       	mov    ecx,0x5db7d4
  57a1ad:	e8 ee 16 f8 ff       	call   0x4fb8a0
  57a1b2:	84 c0                	test   al,al
  57a1b4:	74 55                	je     0x57a20b
  57a1b6:	8b d6                	mov    edx,esi
  57a1b8:	8b cf                	mov    ecx,edi
  57a1ba:	e8 f1 5f ea ff       	call   0x4201b0
  57a1bf:	69 cf 68 05 00 00    	imul   ecx,edi,0x568
  57a1c5:	6a 45                	push   0x45
  57a1c7:	68 e0 b7 5d 00       	push   0x5db7e0
  57a1cc:	80 b9 6a 16 15 06 45 	cmp    BYTE PTR [ecx+0x615166a],0x45

  57a1d3:	0f 94 c0             	sete   al
  57a1d6:	fe c8                	dec    al
  57a1d8:	24 45                	and    al,0x45
  57a1da:	88 81 6a 16 15 06    	mov    BYTE PTR [ecx+0x615166a],al
  57a1e0:	8d 84 24 30 0b 02 00 	lea    eax,[esp+0x20b30]
  57a1e7:	50                   	push   eax
  57a1e8:	c6 81 6a 16 15 06 45 	mov    BYTE PTR [ecx+0x615166a],0x45
  57a1ef:	e8 dc 6e e8 ff       	call   0x4010d0
  57a1f4:	83 c4 0c             	add    esp,0xc
  57a1f7:	5f                   	pop    edi
  57a1f8:	5e                   	pop    esi
  57a1f9:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  57a200:	33 cc                	xor    ecx,esp
  57a202:	e8 a7 fe 00 00       	call   0x58a0ae
  57a207:	8b e5                	mov    esp,ebp
  57a209:	5d                   	pop    ebp
  57a20a:	c3                   	ret
  57a20b:	b9 ec b7 5d 00       	mov    ecx,0x5db7ec
  57a210:	e8 8b 16 f8 ff       	call   0x4fb8a0
  57a215:	84 c0                	test   al,al
  57a217:	0f 84 bc 00 00 00    	je     0x57a2d9
  57a21d:	8b d6                	mov    edx,esi
  57a21f:	8b cf                	mov    ecx,edi
  57a221:	e8 8a 5f ea ff       	call   0x4201b0
  57a226:	68 96 00 00 00       	push   0x96
  57a22b:	ba 6e 00 00 00       	mov    edx,0x6e
  57a230:	8b cf                	mov    ecx,edi
  57a232:	e8 e9 a4 ea ff       	call   0x424720

  57a294:	e8 c7 72 ea ff       	call   0x421560
  57a299:	3d 18 fc ff ff       	cmp    eax,0xfffffc18
  57a29e:	0f 84 1b 27 00 00    	je     0x57c9bf
  57a2a4:	c7 04 b5 7c 17 15 06 	mov    DWORD PTR [esi*4+0x615177c],0x82
  57a2ab:	82 00 00 00 
  57a2af:	c7 04 b5 a4 17 15 06 	mov    DWORD PTR [esi*4+0x61517a4],0x96
  57a2b6:	96 00 00 00 
  57a2ba:	c7 04 b5 6c 18 15 06 	mov    DWORD PTR [esi*4+0x615186c],0x0
  57a2c1:	00 00 00 00 
  57a2c5:	5f                   	pop    edi
  57a2c6:	5e                   	pop    esi
  57a2c7:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  57a2ce:	33 cc                	xor    ecx,esp
  57a2d0:	e8 d9 fd 00 00       	call   0x58a0ae
  57a2d5:	8b e5                	mov    esp,ebp
  57a2d7:	5d                   	pop    ebp
  57a2d8:	c3                   	ret
  57a2d9:	b9 fc b7 5d 00       	mov    ecx,0x5db7fc
  57a2de:	e8 bd 15 f8 ff       	call   0x4fb8a0
  57a2e3:	84 c0                	test   al,al
  57a2e5:	0f 84 96 00 00 00    	je     0x57a381
  57a2eb:	8b d6                	mov    edx,esi
  57a2ed:	8b cf                	mov    ecx,edi
  57a2ef:	e8 bc 5e ea ff       	call   0x4201b0
  57a2f4:	69 c7 68 05 00 00    	imul   eax,edi,0x568
  57a2fa:	33 c9                	xor    ecx,ecx
  57a2fc:	05 7c 17 15 06       	add    eax,0x615177c
  57a301:	83 38 00             	cmp    DWORD PTR [eax],0x0

  57a33d:	00 00 00 00 
  57a341:	c7 04 85 e4 18 15 06 	mov    DWORD PTR [eax*4+0x61518e4],0x0
  57a348:	00 00 00 00 
  57a34c:	c7 04 85 7c 17 15 06 	mov    DWORD PTR [eax*4+0x615177c],0x96
  57a353:	96 00 00 00 
  57a357:	c7 04 85 a4 17 15 06 	mov    DWORD PTR [eax*4+0x61517a4],0x32
  57a35e:	32 00 00 00 
  57a362:	c7 04 85 6c 18 15 06 	mov    DWORD PTR [eax*4+0x615186c],0x0
  57a369:	00 00 00 00 
  57a36d:	5f                   	pop    edi
  57a36e:	5e                   	pop    esi
  57a36f:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  57a376:	33 cc                	xor    ecx,esp
  57a378:	e8 31 fd 00 00       	call   0x58a0ae
  57a37d:	8b e5                	mov    esp,ebp
  57a37f:	5d                   	pop    ebp
  57a380:	c3                   	ret
  57a381:	b9 04 b8 5d 00       	mov    ecx,0x5db804
  57a386:	e8 15 15 f8 ff       	call   0x4fb8a0
  57a38b:	84 c0                	test   al,al
  57a38d:	74 39                	je     0x57a3c8
  57a38f:	b2 01                	mov    dl,0x1
  57a391:	8b cf                	mov    ecx,edi
  57a393:	e8 28 a3 f0 ff       	call   0x4846c0
  57a398:	50                   	push   eax
  57a399:	51                   	push   ecx
  57a39a:	32 d2                	xor    dl,dl
  57a39c:	8b cf                	mov    ecx,edi

  57a38f:	b2 01                	mov    dl,0x1
  57a391:	8b cf                	mov    ecx,edi
  57a393:	e8 28 a3 f0 ff       	call   0x4846c0
  57a398:	50                   	push   eax
  57a399:	51                   	push   ecx
  57a39a:	32 d2                	xor    dl,dl
  57a39c:	8b cf                	mov    ecx,edi
  57a39e:	e8 1d a3 f0 ff       	call   0x4846c0
  57a3a3:	83 c4 04             	add    esp,0x4
  57a3a6:	50                   	push   eax
  57a3a7:	8d 84 24 30 0b 02 00 	lea    eax,[esp+0x20b30]
  57a3ae:	68 18 b8 5d 00       	push   0x5db818
  57a3b3:	50                   	push   eax
  57a3b4:	e8 17 6d e8 ff       	call   0x4010d0
  57a3b9:	83 c4 10             	add    esp,0x10
  57a3bc:	8d 8c 24 28 0b 02 00 	lea    ecx,[esp+0x20b28]
  57a3c3:	e8 48 c1 f7 ff       	call   0x4f6510
  57a3c8:	b9 30 b8 5d 00       	mov    ecx,0x5db830
  57a3cd:	e8 ce 14 f8 ff       	call   0x4fb8a0
  57a3d2:	84 c0                	test   al,al
  57a3d4:	0f 84 01 02 00 00    	je     0x57a5db
  57a3da:	68 00 04 00 00       	push   0x400
  57a3df:	8d 84 24 cc 10 02 00 	lea    eax,[esp+0x210cc]
  57a3e6:	6a 00                	push   0x0
  57a3e8:	50                   	push   eax
  57a3e9:	e8 72 0a 01 00       	call   0x58ae60
  57a3ee:	83 c4 0c             	add    esp,0xc
  57a3f1:	c7 44 24 1c 00 00 00 	mov    DWORD PTR [esp+0x1c],0x0

  57a5a8:	83 e1 03             	and    ecx,0x3
  57a5ab:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
  57a5ad:	8b 7c 24 20          	mov    edi,DWORD PTR [esp+0x20]
  57a5b1:	8b 74 24 14          	mov    esi,DWORD PTR [esp+0x14]
  57a5b5:	8b 44 24 1c          	mov    eax,DWORD PTR [esp+0x1c]
  57a5b9:	40                   	inc    eax
  57a5ba:	89 44 24 1c          	mov    DWORD PTR [esp+0x1c],eax
  57a5be:	83 f8 64             	cmp    eax,0x64
  57a5c1:	0f 8c 29 ff ff ff    	jl     0x57a4f0
  57a5c7:	5f                   	pop    edi
  57a5c8:	5e                   	pop    esi
  57a5c9:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  57a5d0:	33 cc                	xor    ecx,esp
  57a5d2:	e8 d7 fa 00 00       	call   0x58a0ae
  57a5d7:	8b e5                	mov    esp,ebp
  57a5d9:	5d                   	pop    ebp
  57a5da:	c3                   	ret
  57a5db:	b9 44 b8 5d 00       	mov    ecx,0x5db844
  57a5e0:	e8 bb 12 f8 ff       	call   0x4fb8a0
  57a5e5:	84 c0                	test   al,al
  57a5e7:	74 22                	je     0x57a60b
  57a5e9:	6a 00                	push   0x0
  57a5eb:	8b d6                	mov    edx,esi
  57a5ed:	8b cf                	mov    ecx,edi
  57a5ef:	e8 4c 84 fb ff       	call   0x532a40
  57a5f4:	83 c4 04             	add    esp,0x4
  57a5f7:	5f                   	pop    edi
  57a5f8:	5e                   	pop    esi

  57c907:	81 ec ac 00 00 00    	sub    esp,0xac
  57c90d:	8b fc                	mov    edi,esp
  57c90f:	f3 a5                	rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
  57c911:	e8 aa 41 f4 ff       	call   0x4c0ac0
  57c916:	81 c4 ac 00 00 00    	add    esp,0xac
  57c91c:	ba 01 00 00 00       	mov    edx,0x1
  57c921:	8b c8                	mov    ecx,eax
  57c923:	e8 58 e4 fe ff       	call   0x56ad80
  57c928:	83 c4 08             	add    esp,0x8
  57c92b:	5f                   	pop    edi
  57c92c:	5e                   	pop    esi
  57c92d:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  57c934:	33 cc                	xor    ecx,esp
  57c936:	e8 73 d7 00 00       	call   0x58a0ae
  57c93b:	8b e5                	mov    esp,ebp
  57c93d:	5d                   	pop    ebp
  57c93e:	c3                   	ret
  57c93f:	b9 90 c1 5d 00       	mov    ecx,0x5dc190
  57c944:	e8 57 ef f7 ff       	call   0x4fb8a0
  57c949:	84 c0                	test   al,al
  57c94b:	0f 84 6e 00 00 00    	je     0x57c9bf
  57c951:	68 10 27 00 00       	push   0x2710
  57c956:	68 18 fc ff ff       	push   0xfffffc18
  57c95b:	8b d6                	mov    edx,esi
  57c95d:	83 c9 ff             	or     ecx,0xffffffff
  57c960:	e8 ab 24 ed ff       	call   0x44ee10
  57c965:	83 c4 08             	add    esp,0x8
  57c968:	5f                   	pop    edi

  57a5db:	b9 44 b8 5d 00       	mov    ecx,0x5db844
  57a5e0:	e8 bb 12 f8 ff       	call   0x4fb8a0
  57a5e5:	84 c0                	test   al,al
  57a5e7:	74 22                	je     0x57a60b
  57a5e9:	6a 00                	push   0x0
  57a5eb:	8b d6                	mov    edx,esi
  57a5ed:	8b cf                	mov    ecx,edi
  57a5ef:	e8 4c 84 fb ff       	call   0x532a40
  57a5f4:	83 c4 04             	add    esp,0x4
  57a5f7:	5f                   	pop    edi
  57a5f8:	5e                   	pop    esi
  57a5f9:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  57a600:	33 cc                	xor    ecx,esp
  57a602:	e8 a7 fa 00 00       	call   0x58a0ae
  57a607:	8b e5                	mov    esp,ebp
  57a609:	5d                   	pop    ebp
  57a60a:	c3                   	ret
  57a60b:	b9 4c b8 5d 00       	mov    ecx,0x5db84c
  57a610:	e8 8b 12 f8 ff       	call   0x4fb8a0
  57a615:	84 c0                	test   al,al
  57a617:	74 21                	je     0x57a63a
  57a619:	69 c7 68 05 00 00    	imul   eax,edi,0x568
  57a61f:	83 88 20 16 15 06 01 	or     DWORD PTR [eax+0x6151620],0x1
  57a626:	5f                   	pop    edi
  57a627:	5e                   	pop    esi
  57a628:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  57a62f:	33 cc                	xor    ecx,esp
  57a631:	e8 78 fa 00 00       	call   0x58a0ae

  57a607:	8b e5                	mov    esp,ebp
  57a609:	5d                   	pop    ebp
  57a60a:	c3                   	ret
  57a60b:	b9 4c b8 5d 00       	mov    ecx,0x5db84c
  57a610:	e8 8b 12 f8 ff       	call   0x4fb8a0
  57a615:	84 c0                	test   al,al
  57a617:	74 21                	je     0x57a63a
  57a619:	69 c7 68 05 00 00    	imul   eax,edi,0x568
  57a61f:	83 88 20 16 15 06 01 	or     DWORD PTR [eax+0x6151620],0x1
  57a626:	5f                   	pop    edi
  57a627:	5e                   	pop    esi
  57a628:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  57a62f:	33 cc                	xor    ecx,esp
  57a631:	e8 78 fa 00 00       	call   0x58a0ae
  57a636:	8b e5                	mov    esp,ebp
  57a638:	5d                   	pop    ebp
  57a639:	c3                   	ret
  57a63a:	b9 58 b8 5d 00       	mov    ecx,0x5db858
  57a63f:	e8 5c 12 f8 ff       	call   0x4fb8a0
  57a644:	84 c0                	test   al,al
  57a646:	74 2e                	je     0x57a676
  57a648:	ba 01 00 00 00       	mov    edx,0x1
  57a64d:	8b cf                	mov    ecx,edi
  57a64f:	e8 5c ae ea ff       	call   0x4254b0
  57a654:	50                   	push   eax
  57a655:	8d 84 24 2c 0b 02 00 	lea    eax,[esp+0x20b2c]
  57a65c:	68 bc 03 59 00       	push   0x5903bc
  57a661:	50                   	push   eax

  57a638:	5d                   	pop    ebp
  57a639:	c3                   	ret
  57a63a:	b9 58 b8 5d 00       	mov    ecx,0x5db858
  57a63f:	e8 5c 12 f8 ff       	call   0x4fb8a0
  57a644:	84 c0                	test   al,al
  57a646:	74 2e                	je     0x57a676
  57a648:	ba 01 00 00 00       	mov    edx,0x1
  57a64d:	8b cf                	mov    ecx,edi
  57a64f:	e8 5c ae ea ff       	call   0x4254b0
  57a654:	50                   	push   eax
  57a655:	8d 84 24 2c 0b 02 00 	lea    eax,[esp+0x20b2c]
  57a65c:	68 bc 03 59 00       	push   0x5903bc
  57a661:	50                   	push   eax
  57a662:	e8 69 6a e8 ff       	call   0x4010d0
  57a667:	83 c4 0c             	add    esp,0xc
  57a66a:	8d 8c 24 28 0b 02 00 	lea    ecx,[esp+0x20b28]
  57a671:	e8 9a be f7 ff       	call   0x4f6510
  57a676:	b9 64 b8 5d 00       	mov    ecx,0x5db864
  57a67b:	e8 20 12 f8 ff       	call   0x4fb8a0
  57a680:	84 c0                	test   al,al
  57a682:	74 21                	je     0x57a6a5
  57a684:	69 c7 68 05 00 00    	imul   eax,edi,0x568
  57a68a:	80 88 32 16 15 06 10 	or     BYTE PTR [eax+0x6151632],0x10
  57a691:	5f                   	pop    edi
  57a692:	5e                   	pop    esi
  57a693:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  57a69a:	33 cc                	xor    ecx,esp
  57a69c:	e8 0d fa 00 00       	call   0x58a0ae

  57a667:	83 c4 0c             	add    esp,0xc
  57a66a:	8d 8c 24 28 0b 02 00 	lea    ecx,[esp+0x20b28]
  57a671:	e8 9a be f7 ff       	call   0x4f6510
  57a676:	b9 64 b8 5d 00       	mov    ecx,0x5db864
  57a67b:	e8 20 12 f8 ff       	call   0x4fb8a0
  57a680:	84 c0                	test   al,al
  57a682:	74 21                	je     0x57a6a5
  57a684:	69 c7 68 05 00 00    	imul   eax,edi,0x568
  57a68a:	80 88 32 16 15 06 10 	or     BYTE PTR [eax+0x6151632],0x10
  57a691:	5f                   	pop    edi
  57a692:	5e                   	pop    esi
  57a693:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
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
  57a6cb:	e8 50 ea e9 ff       	call   0x419120
  57a6d0:	83 f8 ff             	cmp    eax,0xffffffff

  57a6c5:	8b 0d 3c bd 72 0a    	mov    ecx,DWORD PTR ds:0xa72bd3c
  57a6cb:	e8 50 ea e9 ff       	call   0x419120
  57a6d0:	83 f8 ff             	cmp    eax,0xffffffff
  57a6d3:	8b cf                	mov    ecx,edi
  57a6d5:	6a 00                	push   0x0
  57a6d7:	0f 44 c6             	cmove  eax,esi
  57a6da:	8b d0                	mov    edx,eax
  57a6dc:	e8 ff 81 fb ff       	call   0x5328e0
  57a6e1:	83 c4 04             	add    esp,0x4
  57a6e4:	5f                   	pop    edi
  57a6e5:	5e                   	pop    esi
  57a6e6:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  57a6ed:	33 cc                	xor    ecx,esp
  57a6ef:	e8 ba f9 00 00       	call   0x58a0ae
  57a6f4:	8b e5                	mov    esp,ebp
  57a6f6:	5d                   	pop    ebp
  57a6f7:	c3                   	ret
  57a6f8:	b9 a8 ae 5d 00       	mov    ecx,0x5daea8
  57a6fd:	e8 9e 11 f8 ff       	call   0x4fb8a0
  57a702:	84 c0                	test   al,al
  57a704:	74 24                	je     0x57a72a
  57a706:	69 c7 68 05 00 00    	imul   eax,edi,0x568
  57a70c:	81 88 34 16 15 06 80 	or     DWORD PTR [eax+0x6151634],0x80
  57a713:	00 00 00 
  57a716:	5f                   	pop    edi
  57a717:	5e                   	pop    esi
  57a718:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  57a71f:	33 cc                	xor    ecx,esp

  57a6f6:	5d                   	pop    ebp
  57a6f7:	c3                   	ret
  57a6f8:	b9 a8 ae 5d 00       	mov    ecx,0x5daea8
  57a6fd:	e8 9e 11 f8 ff       	call   0x4fb8a0
  57a702:	84 c0                	test   al,al
  57a704:	74 24                	je     0x57a72a
  57a706:	69 c7 68 05 00 00    	imul   eax,edi,0x568
  57a70c:	81 88 34 16 15 06 80 	or     DWORD PTR [eax+0x6151634],0x80
  57a713:	00 00 00 
  57a716:	5f                   	pop    edi
  57a717:	5e                   	pop    esi
  57a718:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  57a71f:	33 cc                	xor    ecx,esp
  57a721:	e8 88 f9 00 00       	call   0x58a0ae
  57a726:	8b e5                	mov    esp,ebp
  57a728:	5d                   	pop    ebp
  57a729:	c3                   	ret
  57a72a:	b9 84 b8 5d 00       	mov    ecx,0x5db884
  57a72f:	e8 6c 11 f8 ff       	call   0x4fb8a0
  57a734:	84 c0                	test   al,al
  57a736:	74 32                	je     0x57a76a
  57a738:	69 c7 68 05 00 00    	imul   eax,edi,0x568
  57a73e:	8b cf                	mov    ecx,edi
  57a740:	c7 80 4c 19 15 06 00 	mov    DWORD PTR [eax+0x615194c],0x0
  57a747:	00 00 00 
  57a74a:	e8 11 f7 fa ff       	call   0x529e60
  57a74f:	8b cf                	mov    ecx,edi
  57a751:	e8 9a f6 fa ff       	call   0x529df0

  57a734:	84 c0                	test   al,al
  57a736:	74 32                	je     0x57a76a
  57a738:	69 c7 68 05 00 00    	imul   eax,edi,0x568
  57a73e:	8b cf                	mov    ecx,edi
  57a740:	c7 80 4c 19 15 06 00 	mov    DWORD PTR [eax+0x615194c],0x0
  57a747:	00 00 00 
  57a74a:	e8 11 f7 fa ff       	call   0x529e60
  57a74f:	8b cf                	mov    ecx,edi
  57a751:	e8 9a f6 fa ff       	call   0x529df0
  57a756:	5f                   	pop    edi
  57a757:	5e                   	pop    esi
  57a758:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  57a75f:	33 cc                	xor    ecx,esp
  57a761:	e8 48 f9 00 00       	call   0x58a0ae
  57a766:	8b e5                	mov    esp,ebp
  57a768:	5d                   	pop    ebp
  57a769:	c3                   	ret
  57a76a:	b9 90 b8 5d 00       	mov    ecx,0x5db890
  57a76f:	e8 2c 11 f8 ff       	call   0x4fb8a0
  57a774:	84 c0                	test   al,al
  57a776:	74 33                	je     0x57a7ab
  57a778:	69 c7 68 05 00 00    	imul   eax,edi,0x568
  57a77e:	33 c9                	xor    ecx,ecx
  57a780:	8d 51 01             	lea    edx,[ecx+0x1]
  57a783:	66 89 88 98 14 15 06 	mov    WORD PTR [eax+0x6151498],cx
  57a78a:	89 88 7c 17 15 06    	mov    DWORD PTR [eax+0x615177c],ecx
  57a790:	8b cf                	mov    ecx,edi
  57a792:	e8 09 66 ea ff       	call   0x420da0

  57a774:	84 c0                	test   al,al
  57a776:	74 33                	je     0x57a7ab
  57a778:	69 c7 68 05 00 00    	imul   eax,edi,0x568
  57a77e:	33 c9                	xor    ecx,ecx
  57a780:	8d 51 01             	lea    edx,[ecx+0x1]
  57a783:	66 89 88 98 14 15 06 	mov    WORD PTR [eax+0x6151498],cx
  57a78a:	89 88 7c 17 15 06    	mov    DWORD PTR [eax+0x615177c],ecx
  57a790:	8b cf                	mov    ecx,edi
  57a792:	e8 09 66 ea ff       	call   0x420da0
  57a797:	5f                   	pop    edi
  57a798:	5e                   	pop    esi
  57a799:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  57a7a0:	33 cc                	xor    ecx,esp
  57a7a2:	e8 07 f9 00 00       	call   0x58a0ae
  57a7a7:	8b e5                	mov    esp,ebp
  57a7a9:	5d                   	pop    ebp
  57a7aa:	c3                   	ret
  57a7ab:	b9 98 b8 5d 00       	mov    ecx,0x5db898
  57a7b0:	e8 eb 10 f8 ff       	call   0x4fb8a0
  57a7b5:	84 c0                	test   al,al
  57a7b7:	74 0e                	je     0x57a7c7
  57a7b9:	69 c7 68 05 00 00    	imul   eax,edi,0x568
  57a7bf:	fe 80 39 16 15 06    	inc    BYTE PTR [eax+0x6151639]
  57a7c5:	eb 15                	jmp    0x57a7dc
  57a7c7:	b9 a4 b8 5d 00       	mov    ecx,0x5db8a4
  57a7cc:	e8 cf 10 f8 ff       	call   0x4fb8a0
  57a7d1:	84 c0                	test   al,al
  57a7d3:	74 07                	je     0x57a7dc

  57a790:	8b cf                	mov    ecx,edi
  57a792:	e8 09 66 ea ff       	call   0x420da0
  57a797:	5f                   	pop    edi
  57a798:	5e                   	pop    esi
  57a799:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  57a7a0:	33 cc                	xor    ecx,esp
  57a7a2:	e8 07 f9 00 00       	call   0x58a0ae
  57a7a7:	8b e5                	mov    esp,ebp
  57a7a9:	5d                   	pop    ebp
  57a7aa:	c3                   	ret
  57a7ab:	b9 98 b8 5d 00       	mov    ecx,0x5db898
  57a7b0:	e8 eb 10 f8 ff       	call   0x4fb8a0
  57a7b5:	84 c0                	test   al,al
  57a7b7:	74 0e                	je     0x57a7c7
  57a7b9:	69 c7 68 05 00 00    	imul   eax,edi,0x568
  57a7bf:	fe 80 39 16 15 06    	inc    BYTE PTR [eax+0x6151639]
  57a7c5:	eb 15                	jmp    0x57a7dc
  57a7c7:	b9 a4 b8 5d 00       	mov    ecx,0x5db8a4
  57a7cc:	e8 cf 10 f8 ff       	call   0x4fb8a0
  57a7d1:	84 c0                	test   al,al
  57a7d3:	74 07                	je     0x57a7dc
  57a7d5:	8b cf                	mov    ecx,edi
  57a7d7:	e8 94 17 f3 ff       	call   0x4abf70
  57a7dc:	b9 b0 b8 5d 00       	mov    ecx,0x5db8b0
  57a7e1:	e8 ba 10 f8 ff       	call   0x4fb8a0
  57a7e6:	84 c0                	test   al,al
  57a7e8:	74 21                	je     0x57a80b
  57a7ea:	69 c7 68 05 00 00    	imul   eax,edi,0x568

  57a7a2:	e8 07 f9 00 00       	call   0x58a0ae
  57a7a7:	8b e5                	mov    esp,ebp
  57a7a9:	5d                   	pop    ebp
  57a7aa:	c3                   	ret
  57a7ab:	b9 98 b8 5d 00       	mov    ecx,0x5db898
  57a7b0:	e8 eb 10 f8 ff       	call   0x4fb8a0
  57a7b5:	84 c0                	test   al,al
  57a7b7:	74 0e                	je     0x57a7c7
  57a7b9:	69 c7 68 05 00 00    	imul   eax,edi,0x568
  57a7bf:	fe 80 39 16 15 06    	inc    BYTE PTR [eax+0x6151639]
  57a7c5:	eb 15                	jmp    0x57a7dc
  57a7c7:	b9 a4 b8 5d 00       	mov    ecx,0x5db8a4
  57a7cc:	e8 cf 10 f8 ff       	call   0x4fb8a0
  57a7d1:	84 c0                	test   al,al
  57a7d3:	74 07                	je     0x57a7dc
  57a7d5:	8b cf                	mov    ecx,edi
  57a7d7:	e8 94 17 f3 ff       	call   0x4abf70
  57a7dc:	b9 b0 b8 5d 00       	mov    ecx,0x5db8b0
  57a7e1:	e8 ba 10 f8 ff       	call   0x4fb8a0
  57a7e6:	84 c0                	test   al,al
  57a7e8:	74 21                	je     0x57a80b
  57a7ea:	69 c7 68 05 00 00    	imul   eax,edi,0x568
  57a7f0:	c6 80 c7 14 15 06 04 	mov    BYTE PTR [eax+0x61514c7],0x4
  57a7f7:	5f                   	pop    edi
  57a7f8:	5e                   	pop    esi
  57a7f9:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  57a800:	33 cc                	xor    ecx,esp
  57a802:	e8 a7 f8 00 00       	call   0x58a0ae

  57a7dc:	b9 b0 b8 5d 00       	mov    ecx,0x5db8b0
  57a7e1:	e8 ba 10 f8 ff       	call   0x4fb8a0
  57a7e6:	84 c0                	test   al,al
  57a7e8:	74 21                	je     0x57a80b
  57a7ea:	69 c7 68 05 00 00    	imul   eax,edi,0x568
  57a7f0:	c6 80 c7 14 15 06 04 	mov    BYTE PTR [eax+0x61514c7],0x4
  57a7f7:	5f                   	pop    edi
  57a7f8:	5e                   	pop    esi
  57a7f9:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  57a800:	33 cc                	xor    ecx,esp
  57a802:	e8 a7 f8 00 00       	call   0x58a0ae
  57a807:	8b e5                	mov    esp,ebp
  57a809:	5d                   	pop    ebp
  57a80a:	c3                   	ret
  57a80b:	69 f7 68 05 00 00    	imul   esi,edi,0x568
  57a811:	80 be c7 14 15 06 04 	cmp    BYTE PTR [esi+0x61514c7],0x4
  57a818:	75 29                	jne    0x57a843
  57a81a:	b9 b8 b8 5d 00       	mov    ecx,0x5db8b8
  57a81f:	e8 7c 10 f8 ff       	call   0x4fb8a0
  57a824:	84 c0                	test   al,al
  57a826:	74 1b                	je     0x57a843
  57a828:	c6 86 c7 14 15 06 00 	mov    BYTE PTR [esi+0x61514c7],0x0
  57a82f:	5f                   	pop    edi
  57a830:	5e                   	pop    esi
  57a831:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  57a838:	33 cc                	xor    ecx,esp
  57a83a:	e8 6f f8 00 00       	call   0x58a0ae
  57a83f:	8b e5                	mov    esp,ebp

  57a80a:	c3                   	ret
  57a80b:	69 f7 68 05 00 00    	imul   esi,edi,0x568
  57a811:	80 be c7 14 15 06 04 	cmp    BYTE PTR [esi+0x61514c7],0x4
  57a818:	75 29                	jne    0x57a843
  57a81a:	b9 b8 b8 5d 00       	mov    ecx,0x5db8b8
  57a81f:	e8 7c 10 f8 ff       	call   0x4fb8a0
  57a824:	84 c0                	test   al,al
  57a826:	74 1b                	je     0x57a843
  57a828:	c6 86 c7 14 15 06 00 	mov    BYTE PTR [esi+0x61514c7],0x0
  57a82f:	5f                   	pop    edi
  57a830:	5e                   	pop    esi
  57a831:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  57a838:	33 cc                	xor    ecx,esp
  57a83a:	e8 6f f8 00 00       	call   0x58a0ae
  57a83f:	8b e5                	mov    esp,ebp
  57a841:	5d                   	pop    ebp
  57a842:	c3                   	ret
  57a843:	b9 d0 b8 5d 00       	mov    ecx,0x5db8d0
  57a848:	e8 53 10 f8 ff       	call   0x4fb8a0
  57a84d:	84 c0                	test   al,al
  57a84f:	74 39                	je     0x57a88a
  57a851:	8a 86 dd 15 15 06    	mov    al,BYTE PTR [esi+0x61515dd]
  57a857:	a8 01                	test   al,0x1
  57a859:	75 14                	jne    0x57a86f
  57a85b:	0c 01                	or     al,0x1
  57a85d:	b9 e0 b8 5d 00       	mov    ecx,0x5db8e0
  57a862:	88 86 dd 15 15 06    	mov    BYTE PTR [esi+0x61515dd],al
  57a868:	e8 a3 bc f7 ff       	call   0x4f6510

  57a84d:	84 c0                	test   al,al
  57a84f:	74 39                	je     0x57a88a
  57a851:	8a 86 dd 15 15 06    	mov    al,BYTE PTR [esi+0x61515dd]
  57a857:	a8 01                	test   al,0x1
  57a859:	75 14                	jne    0x57a86f
  57a85b:	0c 01                	or     al,0x1
  57a85d:	b9 e0 b8 5d 00       	mov    ecx,0x5db8e0
  57a862:	88 86 dd 15 15 06    	mov    BYTE PTR [esi+0x61515dd],al
  57a868:	e8 a3 bc f7 ff       	call   0x4f6510
  57a86d:	eb 22                	jmp    0x57a891
  57a86f:	24 fe                	and    al,0xfe
  57a871:	b9 e4 b8 5d 00       	mov    ecx,0x5db8e4
  57a876:	88 86 dd 15 15 06    	mov    BYTE PTR [esi+0x61515dd],al
  57a87c:	e8 8f bc f7 ff       	call   0x4f6510
  57a881:	c6 86 01 14 15 06 00 	mov    BYTE PTR [esi+0x6151401],0x0
  57a888:	eb 07                	jmp    0x57a891
  57a88a:	80 a6 dd 15 15 06 f7 	and    BYTE PTR [esi+0x61515dd],0xf7
  57a891:	b9 ec b8 5d 00       	mov    ecx,0x5db8ec
  57a896:	e8 05 10 f8 ff       	call   0x4fb8a0
  57a89b:	84 c0                	test   al,al
  57a89d:	74 2e                	je     0x57a8cd
  57a89f:	8b 96 70 17 15 06    	mov    edx,DWORD PTR [esi+0x6151770]
  57a8a5:	8b 8e 6c 17 15 06    	mov    ecx,DWORD PTR [esi+0x615176c]
  57a8ab:	e8 60 17 f7 ff       	call   0x4ec010
  57a8b0:	69 c0 9c 00 00 00    	imul   eax,eax,0x9c
  57a8b6:	8b 80 6c 2b 42 06    	mov    eax,DWORD PTR [eax+0x6422b6c]
  57a8bc:	85 c0                	test   eax,eax
  57a8be:	74 0d                	je     0x57a8cd

  57a87c:	e8 8f bc f7 ff       	call   0x4f6510
  57a881:	c6 86 01 14 15 06 00 	mov    BYTE PTR [esi+0x6151401],0x0
  57a888:	eb 07                	jmp    0x57a891
  57a88a:	80 a6 dd 15 15 06 f7 	and    BYTE PTR [esi+0x61515dd],0xf7
  57a891:	b9 ec b8 5d 00       	mov    ecx,0x5db8ec
  57a896:	e8 05 10 f8 ff       	call   0x4fb8a0
  57a89b:	84 c0                	test   al,al
  57a89d:	74 2e                	je     0x57a8cd
  57a89f:	8b 96 70 17 15 06    	mov    edx,DWORD PTR [esi+0x6151770]
  57a8a5:	8b 8e 6c 17 15 06    	mov    ecx,DWORD PTR [esi+0x615176c]
  57a8ab:	e8 60 17 f7 ff       	call   0x4ec010
  57a8b0:	69 c0 9c 00 00 00    	imul   eax,eax,0x9c
  57a8b6:	8b 80 6c 2b 42 06    	mov    eax,DWORD PTR [eax+0x6422b6c]
  57a8bc:	85 c0                	test   eax,eax
  57a8be:	74 0d                	je     0x57a8cd
  57a8c0:	89 86 60 14 15 06    	mov    DWORD PTR [esi+0x6151460],eax
  57a8c6:	c6 86 77 14 15 06 00 	mov    BYTE PTR [esi+0x6151477],0x0
  57a8cd:	b9 fc b8 5d 00       	mov    ecx,0x5db8fc
  57a8d2:	e8 c9 0f f8 ff       	call   0x4fb8a0
  57a8d7:	84 c0                	test   al,al
  57a8d9:	0f 84 e0 20 00 00    	je     0x57c9bf
  57a8df:	80 be 00 14 15 06 01 	cmp    BYTE PTR [esi+0x6151400],0x1
  57a8e6:	8b cf                	mov    ecx,edi
  57a8e8:	74 59                	je     0x57a943
  57a8ea:	e8 f1 f7 f2 ff       	call   0x4aa0e0
  57a8ef:	85 c0                	test   eax,eax
  57a8f1:	75 11                	jne    0x57a904
  57a8f3:	c7 86 60 14 15 06 ff 	mov    DWORD PTR [esi+0x6151460],0xffffffff

  57a959:	05 00 ff ff ff       	add    eax,0xffffff00
  57a95e:	89 86 e4 15 15 06    	mov    DWORD PTR [esi+0x61515e4],eax
  57a964:	81 a6 ec 16 15 06 ff 	and    DWORD PTR [esi+0x61516ec],0xfffbfeff
  57a96b:	fe fb ff 
  57a96e:	5f                   	pop    edi
  57a96f:	5e                   	pop    esi
  57a970:	8b 8c 24 c4 1c 02 00 	mov    ecx,DWORD PTR [esp+0x21cc4]
  57a977:	33 cc                	xor    ecx,esp
  57a979:	e8 30 f7 00 00       	call   0x58a0ae
  57a97e:	8b e5                	mov    esp,ebp
  57a980:	5d                   	pop    ebp
  57a981:	c3                   	ret
  57a982:	a9 00 01 00 00       	test   eax,0x100
  57a987:	75 05                	jne    0x57a98e
  57a989:	05 00 01 00 00       	add    eax,0x100
  57a98e:	89 86 e4 15 15 06    	mov    DWORD PTR [esi+0x61515e4],eax
  57a994:	b9 30 b9 5d 00       	mov    ecx,0x5db930
  57a999:	c6 86 86 14 15 06 03 	mov    BYTE PTR [esi+0x6151486],0x3
  57a9a0:	e8 fb 0e f8 ff       	call   0x4fb8a0
  57a9a5:	84 c0                	test   al,al
  57a9a7:	74 1c                	je     0x57a9c5
  57a9a9:	c6 86 67 16 15 06 02 	mov    BYTE PTR [esi+0x6151667],0x2
  57a9b0:	ba 03 00 00 00       	mov    edx,0x3
  57a9b5:	80 8e 68 16 15 06 03 	or     BYTE PTR [esi+0x6151668],0x3
  57a9bc:	8b cf                	mov    ecx,edi
  57a9be:	e8 dd 08 f3 ff       	call   0x4ab2a0
  57a9c3:	eb 0a                	jmp    0x57a9cf
  57a9c5:	81 a6 ec 16 15 06 ff 	and    DWORD PTR [esi+0x61516ec],0xfffffeff

  57a982:	a9 00 01 00 00       	test   eax,0x100
  57a987:	75 05                	jne    0x57a98e
  57a989:	05 00 01 00 00       	add    eax,0x100
  57a98e:	89 86 e4 15 15 06    	mov    DWORD PTR [esi+0x61515e4],eax
  57a994:	b9 30 b9 5d 00       	mov    ecx,0x5db930
  57a999:	c6 86 86 14 15 06 03 	mov    BYTE PTR [esi+0x6151486],0x3
  57a9a0:	e8 fb 0e f8 ff       	call   0x4fb8a0
  57a9a5:	84 c0                	test   al,al
  57a9a7:	74 1c                	je     0x57a9c5
  57a9a9:	c6 86 67 16 15 06 02 	mov    BYTE PTR [esi+0x6151667],0x2
  57a9b0:	ba 03 00 00 00       	mov    edx,0x3
  57a9b5:	80 8e 68 16 15 06 03 	or     BYTE PTR [esi+0x6151668],0x3
  57a9bc:	8b cf                	mov    ecx,edi
  57a9be:	e8 dd 08 f3 ff       	call   0x4ab2a0
  57a9c3:	eb 0a                	jmp    0x57a9cf
  57a9c5:	81 a6 ec 16 15 06 ff 	and    DWORD PTR [esi+0x61516ec],0xfffffeff
  57a9cc:	fe ff ff 
  57a9cf:	b9 3c b9 5d 00       	mov    ecx,0x5db93c
  57a9d4:	e8 c7 0e f8 ff       	call   0x4fb8a0
  57a9d9:	84 c0                	test   al,al
  57a9db:	0f 84 de 1f 00 00    	je     0x57c9bf
  57a9e1:	8b 86 e4 15 15 06    	mov    eax,DWORD PTR [esi+0x61515e4]
  57a9e7:	84 c0                	test   al,al
  57a9e9:	78 03                	js     0x57a9ee
  57a9eb:	83 e8 80             	sub    eax,0xffffff80
  57a9ee:	89 86 e4 15 15 06    	mov    DWORD PTR [esi+0x61515e4],eax
  57a9f4:	5f                   	pop    edi
  57a9f5:	5e                   	pop    esi

  48b5be:	e8 4d af 06 00       	call   0x4f6510
  48b5c3:	ff 35 c4 b1 72 0a    	push   DWORD PTR ds:0xa72b1c4
  48b5c9:	8d 85 90 fb ff ff    	lea    eax,[ebp-0x470]
  48b5cf:	ff b5 fc f7 ff ff    	push   DWORD PTR [ebp-0x804]
  48b5d5:	68 4c d1 59 00       	push   0x59d14c
  48b5da:	50                   	push   eax
  48b5db:	e8 f0 5a f7 ff       	call   0x4010d0
  48b5e0:	8d 8d 90 fb ff ff    	lea    ecx,[ebp-0x470]
  48b5e6:	e8 25 af 06 00       	call   0x4f6510
  48b5eb:	ff b5 54 fb ff ff    	push   DWORD PTR [ebp-0x4ac]
  48b5f1:	8d 85 90 fb ff ff    	lea    eax,[ebp-0x470]
  48b5f7:	68 60 d1 59 00       	push   0x59d160
  48b5fc:	50                   	push   eax
  48b5fd:	e8 ce 5a f7 ff       	call   0x4010d0
  48b602:	83 c4 2c             	add    esp,0x2c
  48b605:	8d 8d 90 fb ff ff    	lea    ecx,[ebp-0x470]
  48b60b:	e8 00 af 06 00       	call   0x4f6510
  48b610:	b9 6c d1 59 00       	mov    ecx,0x59d16c
  48b615:	e8 86 02 07 00       	call   0x4fb8a0
  48b61a:	84 c0                	test   al,al
  48b61c:	74 5d                	je     0x48b67b
  48b61e:	8b 8d 54 fb ff ff    	mov    ecx,DWORD PTR [ebp-0x4ac]
  48b624:	8a d3                	mov    dl,bl
  48b626:	e8 a5 1d f8 ff       	call   0x40d3d0
  48b62b:	8b d0                	mov    edx,eax
  48b62d:	e8 ee d7 f8 ff       	call   0x418e20
  48b632:	8b 0d 9c 1c 6d 0a    	mov    ecx,DWORD PTR ds:0xa6d1c9c
  48b638:	41                   	inc    ecx

  43615a:	cc                   	int3
  43615b:	cc                   	int3
  43615c:	cc                   	int3
  43615d:	cc                   	int3
  43615e:	cc                   	int3
  43615f:	cc                   	int3
  436160:	55                   	push   ebp
  436161:	8b ec                	mov    ebp,esp
  436163:	83 ec 0c             	sub    esp,0xc
  436166:	83 ca ff             	or     edx,0xffffffff
  436169:	0b ca                	or     ecx,edx
  43616b:	53                   	push   ebx
  43616c:	56                   	push   esi
  43616d:	57                   	push   edi
  43616e:	e8 5d 98 06 00       	call   0x49f9d0
  436173:	85 c0                	test   eax,eax
  436175:	74 1e                	je     0x436195
  436177:	b9 d8 3b 59 00       	mov    ecx,0x593bd8
  43617c:	e8 1f 57 0c 00       	call   0x4fb8a0
  436181:	84 c0                	test   al,al
  436183:	74 10                	je     0x436195
  436185:	51                   	push   ecx
  436186:	e8 e5 fc ff ff       	call   0x435e70
  43618b:	83 c4 04             	add    esp,0x4
  43618e:	5f                   	pop    edi
  43618f:	5e                   	pop    esi
  436190:	5b                   	pop    ebx
  436191:	8b e5                	mov    esp,ebp

  436270:	83 f8 ff             	cmp    eax,0xffffffff
  436273:	74 0b                	je     0x436280
  436275:	8d 04 c0             	lea    eax,[eax+eax*8]
  436278:	0f b7 1c 85 b0 28 6d 	movzx  ebx,WORD PTR [eax*4+0xa6d28b0]
  43627f:	0a 
  436280:	85 db                	test   ebx,ebx
  436282:	75 21                	jne    0x4362a5
  436284:	8b 1d 40 bd 72 0a    	mov    ebx,DWORD PTR ds:0xa72bd40
  43628a:	8b 0d 9c 1c 6d 0a    	mov    ecx,DWORD PTR ds:0xa6d1c9c
  436290:	8b 55 fc             	mov    edx,DWORD PTR [ebp-0x4]
  436293:	46                   	inc    esi
  436294:	8d 41 01             	lea    eax,[ecx+0x1]
  436297:	42                   	inc    edx
  436298:	89 55 fc             	mov    DWORD PTR [ebp-0x4],edx
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

  4350b2:	5d                   	pop    ebp
  4350b3:	c3                   	ret
  4350b4:	f6 05 e0 52 91 05 70 	test   BYTE PTR ds:0x59152e0,0x70
  4350bb:	74 4a                	je     0x435107
  4350bd:	8b 0c bd d0 ac 72 0a 	mov    ecx,DWORD PTR [edi*4+0xa72acd0]
  4350c4:	ba 01 00 00 00       	mov    edx,0x1
  4350c9:	6a 04                	push   0x4
  4350cb:	e8 a0 c6 01 00       	call   0x451770
  4350d0:	83 c4 04             	add    esp,0x4
  4350d3:	50                   	push   eax
  4350d4:	68 10 39 59 00       	push   0x593910
  4350d9:	8d 84 24 10 02 00 00 	lea    eax,[esp+0x210]
  4350e0:	50                   	push   eax
  4350e1:	e8 ea bf fc ff       	call   0x4010d0
  4350e6:	83 c4 0c             	add    esp,0xc
  4350e9:	8d 8c 24 08 02 00 00 	lea    ecx,[esp+0x208]
  4350f0:	e8 1b 14 0c 00       	call   0x4f6510
  4350f5:	b9 30 39 59 00       	mov    ecx,0x593930
  4350fa:	e8 a1 67 0c 00       	call   0x4fb8a0
  4350ff:	84 c0                	test   al,al
  435101:	0f 84 4b 09 00 00    	je     0x435a52
  435107:	8b 35 5c 52 91 05    	mov    esi,DWORD PTR ds:0x591525c
  43510d:	66 0f 6e 44 24 24    	movd   xmm0,DWORD PTR [esp+0x24]
  435113:	83 ec 08             	sub    esp,0x8
  435116:	0f 5b c0             	cvtdq2ps xmm0,xmm0
  435119:	f3 0f 59 44 24 14    	mulss  xmm0,DWORD PTR [esp+0x14]
  43511f:	0f 5a c0             	cvtps2pd xmm0,xmm0
  435122:	f2 0f 11 44 24 18    	movsd  QWORD PTR [esp+0x18],xmm0

  56c57e:	85 f6                	test   esi,esi
  56c580:	0f 84 e4 00 00 00    	je     0x56c66a
  56c586:	8b b5 e4 fb ff ff    	mov    esi,DWORD PTR [ebp-0x41c]
  56c58c:	8b 0f                	mov    ecx,DWORD PTR [edi]
  56c58e:	ff 85 cc fb ff ff    	inc    DWORD PTR [ebp-0x434]
  56c594:	6a 01                	push   0x1
  56c596:	0f b7 16             	movzx  edx,WORD PTR [esi]
  56c599:	e8 a2 60 ee ff       	call   0x452640
  56c59e:	83 c4 04             	add    esp,0x4
  56c5a1:	50                   	push   eax
  56c5a2:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  56c5a8:	68 f4 9d 5d 00       	push   0x5d9df4
  56c5ad:	50                   	push   eax
  56c5ae:	e8 1d 4b e9 ff       	call   0x4010d0
  56c5b3:	83 c4 0c             	add    esp,0xc
  56c5b6:	8d 8d f8 fb ff ff    	lea    ecx,[ebp-0x408]
  56c5bc:	e8 4f 9f f8 ff       	call   0x4f6510
  56c5c1:	b9 14 9e 5d 00       	mov    ecx,0x5d9e14
  56c5c6:	e8 d5 f2 f8 ff       	call   0x4fb8a0
  56c5cb:	8b 95 ec fb ff ff    	mov    edx,DWORD PTR [ebp-0x414]
  56c5d1:	84 c0                	test   al,al
  56c5d3:	8b 85 f0 fb ff ff    	mov    eax,DWORD PTR [ebp-0x410]
  56c5d9:	0f 84 97 00 00 00    	je     0x56c676
  56c5df:	33 c9                	xor    ecx,ecx
  56c5e1:	ff 85 c8 fb ff ff    	inc    DWORD PTR [ebp-0x438]
  56c5e7:	33 f6                	xor    esi,esi
  56c5e9:	66 89 0a             	mov    WORD PTR [edx],cx
  56c5ec:	8b 8d e8 fb ff ff    	mov    ecx,DWORD PTR [ebp-0x418]

  57dae4:	e9 8f 01 00 00       	jmp    0x57dc78
  57dae9:	33 d2                	xor    edx,edx
  57daeb:	8d 4a 69             	lea    ecx,[edx+0x69]
  57daee:	e8 2d 6c fe ff       	call   0x564720
  57daf3:	8b c8                	mov    ecx,eax
  57daf5:	e8 d6 b5 f7 ff       	call   0x4f90d0
  57dafa:	e8 31 b3 ed ff       	call   0x458e30
  57daff:	e9 74 01 00 00       	jmp    0x57dc78
  57db04:	83 3d e4 0d 15 06 00 	cmp    DWORD PTR ds:0x6150de4,0x0
  57db0b:	74 19                	je     0x57db26
  57db0d:	b9 14 c5 5d 00       	mov    ecx,0x5dc514
  57db12:	c7 05 e4 0d 15 06 00 	mov    DWORD PTR ds:0x6150de4,0x0
  57db19:	00 00 00 
  57db1c:	e8 ef 89 f7 ff       	call   0x4f6510
  57db21:	e9 52 01 00 00       	jmp    0x57dc78
  57db26:	b9 2c c5 5d 00       	mov    ecx,0x5dc52c
  57db2b:	e8 e0 89 f7 ff       	call   0x4f6510
  57db30:	b9 40 c5 5d 00       	mov    ecx,0x5dc540
  57db35:	e8 66 dd f7 ff       	call   0x4fb8a0
  57db3a:	84 c0                	test   al,al
  57db3c:	0f 84 36 01 00 00    	je     0x57dc78
  57db42:	b9 54 c5 5d 00       	mov    ecx,0x5dc554
  57db47:	c7 05 e4 0d 15 06 01 	mov    DWORD PTR ds:0x6150de4,0x1
  57db4e:	00 00 00 
  57db51:	e8 ba 89 f7 ff       	call   0x4f6510
  57db56:	b9 68 c5 5d 00       	mov    ecx,0x5dc568
  57db5b:	e8 b0 89 f7 ff       	call   0x4f6510
  57db60:	e9 13 01 00 00       	jmp    0x57dc78

  51fe74:	83 c4 08             	add    esp,0x8
  51fe77:	80 fb 04             	cmp    bl,0x4
  51fe7a:	0f 84 fd 00 00 00    	je     0x51ff7d
  51fe80:	80 fb 05             	cmp    bl,0x5
  51fe83:	0f 84 f4 00 00 00    	je     0x51ff7d
  51fe89:	8b 35 34 1c 6d 0a    	mov    esi,DWORD PTR ds:0xa6d1c34
  51fe8f:	8b d6                	mov    edx,esi
  51fe91:	8b 3d 3c bd 72 0a    	mov    edi,DWORD PTR ds:0xa72bd3c
  51fe97:	8b cf                	mov    ecx,edi
  51fe99:	e8 e2 1c f7 ff       	call   0x491b80
  51fe9e:	85 c0                	test   eax,eax
  51fea0:	74 2b                	je     0x51fecd
  51fea2:	8b d6                	mov    edx,esi
  51fea4:	8b cf                	mov    ecx,edi
  51fea6:	e8 45 c3 f6 ff       	call   0x48c1f0
  51feab:	3c 29                	cmp    al,0x29
  51fead:	74 1e                	je     0x51fecd
  51feaf:	b9 a0 e5 5a 00       	mov    ecx,0x5ae5a0
  51feb4:	e8 e7 b9 fd ff       	call   0x4fb8a0
  51feb9:	84 c0                	test   al,al
  51febb:	0f 84 a3 02 00 00    	je     0x520164
  51fec1:	8b 35 34 1c 6d 0a    	mov    esi,DWORD PTR ds:0xa6d1c34
  51fec7:	8b 3d 3c bd 72 0a    	mov    edi,DWORD PTR ds:0xa72bd3c
  51fecd:	56                   	push   esi
  51fece:	8b d7                	mov    edx,edi
  51fed0:	b9 62 00 00 00       	mov    ecx,0x62
  51fed5:	e8 56 95 ef ff       	call   0x419430
  51feda:	83 c4 04             	add    esp,0x4

  51fedd:	83 f8 ff             	cmp    eax,0xffffffff
  51fee0:	75 1b                	jne    0x51fefd
  51fee2:	6a 02                	push   0x2
  51fee4:	8d 50 22             	lea    edx,[eax+0x22]
  51fee7:	33 c9                	xor    ecx,ecx
  51fee9:	e8 f2 5a f0 ff       	call   0x4259e0
  51feee:	83 c4 04             	add    esp,0x4
  51fef1:	8b 3d 3c bd 72 0a    	mov    edi,DWORD PTR ds:0xa72bd3c
  51fef7:	8b 35 34 1c 6d 0a    	mov    esi,DWORD PTR ds:0xa6d1c34
  51fefd:	68 f0 c9 59 00       	push   0x59c9f0
  51ff02:	6a 00                	push   0x0
  51ff04:	8b d6                	mov    edx,esi
  51ff06:	8b cf                	mov    ecx,edi
  51ff08:	e8 13 5d f6 ff       	call   0x485c20
  51ff0d:	83 c4 08             	add    esp,0x8
  51ff10:	83 f8 01             	cmp    eax,0x1
  51ff13:	7c 12                	jl     0x51ff27
  51ff15:	b9 a0 e5 5a 00       	mov    ecx,0x5ae5a0
  51ff1a:	e8 81 b9 fd ff       	call   0x4fb8a0
  51ff1f:	84 c0                	test   al,al
  51ff21:	0f 84 3d 02 00 00    	je     0x520164
  51ff27:	ba 32 00 00 00       	mov    edx,0x32
  51ff2c:	33 c9                	xor    ecx,ecx
  51ff2e:	e8 ed 92 f1 ff       	call   0x439220
  51ff33:	8b 35 40 bd 72 0a    	mov    esi,DWORD PTR ds:0xa72bd40
  51ff39:	8b d8                	mov    ebx,eax
  51ff3b:	8b 3d 9c 1c 6d 0a    	mov    edi,DWORD PTR ds:0xa6d1c9c
  51ff41:	b9 08 00 00 00       	mov    ecx,0x8

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
  4568cf:	0f 85 98 0c 00 00    	jne    0x45756d
  4568d5:	b9 7c d5 59 00       	mov    ecx,0x59d57c
  4568da:	c7 05 d8 bc 5b 06 00 	mov    DWORD PTR ds:0x65bbcd8,0x0
  4568e1:	00 00 00 
  4568e4:	e8 07 48 0b 00       	call   0x50b0f0
  4568e9:	0f 28 05 c0 da 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5ddac0
  4568f0:	8d 84 24 30 07 00 00 	lea    eax,[esp+0x730]
  4568f7:	50                   	push   eax

  4898c1:	b9 d4 cc 59 00       	mov    ecx,0x59ccd4
  4898c6:	e8 45 cc 06 00       	call   0x4f6510
  4898cb:	c7 05 50 f5 17 02 00 	mov    DWORD PTR ds:0x217f550,0x0
  4898d2:	00 00 00 
  4898d5:	83 cf ff             	or     edi,0xffffffff
  4898d8:	c6 05 e3 cc 58 04 01 	mov    BYTE PTR ds:0x458cce3,0x1
  4898df:	e9 9f 04 00 00       	jmp    0x489d83
  4898e4:	83 f9 fe             	cmp    ecx,0xfffffffe
  4898e7:	75 0f                	jne    0x4898f8
  4898e9:	ba 1b 00 00 00       	mov    edx,0x1b
  4898ee:	8b cb                	mov    ecx,ebx
  4898f0:	89 54 24 4c          	mov    DWORD PTR [esp+0x4c],edx
  4898f4:	89 4c 24 60          	mov    DWORD PTR [esp+0x60],ecx
  4898f8:	83 f8 04             	cmp    eax,0x4
  4898fb:	75 25                	jne    0x489922
  4898fd:	b9 f0 cc 59 00       	mov    ecx,0x59ccf0
  489902:	c7 05 50 f5 17 02 00 	mov    DWORD PTR ds:0x217f550,0x0
  489909:	00 00 00 
  48990c:	e8 ff 21 07 00       	call   0x4fbb10
  489911:	84 c0                	test   al,al
  489913:	74 08                	je     0x48991d
  489915:	83 cf ff             	or     edi,0xffffffff
  489918:	e9 66 04 00 00       	jmp    0x489d83
  48991d:	a1 50 f5 17 02       	mov    eax,ds:0x217f550
  489922:	83 f8 01             	cmp    eax,0x1
  489925:	75 2e                	jne    0x489955
  489927:	b9 fc cc 59 00       	mov    ecx,0x59ccfc
  48992c:	c7 05 50 f5 17 02 00 	mov    DWORD PTR ds:0x217f550,0x0

  4898fd:	b9 f0 cc 59 00       	mov    ecx,0x59ccf0
  489902:	c7 05 50 f5 17 02 00 	mov    DWORD PTR ds:0x217f550,0x0
  489909:	00 00 00 
  48990c:	e8 ff 21 07 00       	call   0x4fbb10
  489911:	84 c0                	test   al,al
  489913:	74 08                	je     0x48991d
  489915:	83 cf ff             	or     edi,0xffffffff
  489918:	e9 66 04 00 00       	jmp    0x489d83
  48991d:	a1 50 f5 17 02       	mov    eax,ds:0x217f550
  489922:	83 f8 01             	cmp    eax,0x1
  489925:	75 2e                	jne    0x489955
  489927:	b9 fc cc 59 00       	mov    ecx,0x59ccfc
  48992c:	c7 05 50 f5 17 02 00 	mov    DWORD PTR ds:0x217f550,0x0
  489933:	00 00 00 
  489936:	e8 f5 a6 09 00       	call   0x524030
  48993b:	84 c0                	test   al,al
  48993d:	74 16                	je     0x489955
  48993f:	b9 f0 cc 59 00       	mov    ecx,0x59ccf0
  489944:	e8 c7 21 07 00       	call   0x4fbb10
  489949:	84 c0                	test   al,al
  48994b:	74 08                	je     0x489955
  48994d:	83 cf ff             	or     edi,0xffffffff
  489950:	e9 2e 04 00 00       	jmp    0x489d83
  489955:	32 c0                	xor    al,al
  489957:	33 ff                	xor    edi,edi
  489959:	89 44 24 54          	mov    DWORD PTR [esp+0x54],eax
  48995d:	0f 1f 00             	nop    DWORD PTR [eax]
  489960:	8d 1c bf             	lea    ebx,[edi+edi*4]

  489b38:	0f 84 ef 00 00 00    	je     0x489c2d
  489b3e:	8a 86 67 14 15 06    	mov    al,BYTE PTR [esi+0x6151467]
  489b44:	3c 63                	cmp    al,0x63
  489b46:	74 08                	je     0x489b50
  489b48:	3c 02                	cmp    al,0x2
  489b4a:	0f 85 dd 00 00 00    	jne    0x489c2d
  489b50:	83 be 50 19 15 06 ff 	cmp    DWORD PTR [esi+0x6151950],0xffffffff
  489b57:	0f 85 d0 00 00 00    	jne    0x489c2d
  489b5d:	80 bc 9c da 00 00 00 	cmp    BYTE PTR [esp+ebx*4+0xda],0x0
  489b64:	00 
  489b65:	75 38                	jne    0x489b9f
  489b67:	e8 74 00 01 00       	call   0x499be0
  489b6c:	b9 10 cd 59 00       	mov    ecx,0x59cd10
  489b71:	89 3d 4c 2a 62 0a    	mov    DWORD PTR ds:0xa622a4c,edi
  489b77:	e8 84 7f 0d 00       	call   0x561b00
  489b7c:	8b c8                	mov    ecx,eax
  489b7e:	e8 8d c9 06 00       	call   0x4f6510
  489b83:	b9 f0 cc 59 00       	mov    ecx,0x59ccf0
  489b88:	e8 83 1f 07 00       	call   0x4fbb10
  489b8d:	84 c0                	test   al,al
  489b8f:	0f 85 5a 02 00 00    	jne    0x489def
  489b95:	66 c7 84 9c d9 00 00 	mov    WORD PTR [esp+ebx*4+0xd9],0x101
  489b9c:	00 01 01 
  489b9f:	a1 9c 1c 6d 0a       	mov    eax,ds:0xa6d1c9c
  489ba4:	2b 86 38 19 15 06    	sub    eax,DWORD PTR [esi+0x6151938]
  489baa:	99                   	cdq
  489bab:	8b c8                	mov    ecx,eax
  489bad:	a1 40 bd 72 0a       	mov    eax,ds:0xa72bd40

  489bc6:	3b 84 9c d0 00 00 00 	cmp    eax,DWORD PTR [esp+ebx*4+0xd0]
  489bcd:	7d 5e                	jge    0x489c2d
  489bcf:	83 f8 05             	cmp    eax,0x5
  489bd2:	7f 59                	jg     0x489c2d
  489bd4:	80 bc 9c db 00 00 00 	cmp    BYTE PTR [esp+ebx*4+0xdb],0x0
  489bdb:	00 
  489bdc:	75 4f                	jne    0x489c2d
  489bde:	e8 fd ff 00 00       	call   0x499be0
  489be3:	80 bc 9c d8 00 00 00 	cmp    BYTE PTR [esp+ebx*4+0xd8],0x0
  489bea:	00 
  489beb:	b9 28 cd 59 00       	mov    ecx,0x59cd28
  489bf0:	89 3d 4c 2a 62 0a    	mov    DWORD PTR ds:0xa622a4c,edi
  489bf6:	74 05                	je     0x489bfd
  489bf8:	b9 44 cd 59 00       	mov    ecx,0x59cd44
  489bfd:	e8 fe 7e 0d 00       	call   0x561b00
  489c02:	8b c8                	mov    ecx,eax
  489c04:	e8 07 c9 06 00       	call   0x4f6510
  489c09:	b9 f0 cc 59 00       	mov    ecx,0x59ccf0
  489c0e:	e8 fd 1e 07 00       	call   0x4fbb10
  489c13:	84 c0                	test   al,al
  489c15:	0f 85 d4 01 00 00    	jne    0x489def
  489c1b:	c6 84 9c db 00 00 00 	mov    BYTE PTR [esp+ebx*4+0xdb],0x1
  489c22:	01 
  489c23:	66 c7 84 9c d8 00 00 	mov    WORD PTR [esp+ebx*4+0xd8],0x101
  489c2a:	00 01 01 
  489c2d:	80 bc 9c d8 00 00 00 	cmp    BYTE PTR [esp+ebx*4+0xd8],0x0
  489c34:	00 
  489c35:	75 59                	jne    0x489c90

  489c35:	75 59                	jne    0x489c90
  489c37:	80 bc 9c d9 00 00 00 	cmp    BYTE PTR [esp+ebx*4+0xd9],0x0
  489c3e:	00 
  489c3f:	75 4f                	jne    0x489c90
  489c41:	8b cf                	mov    ecx,edi
  489c43:	e8 48 fc 01 00       	call   0x4a9890
  489c48:	85 c0                	test   eax,eax
  489c4a:	74 0c                	je     0x489c58
  489c4c:	e8 8f ff 00 00       	call   0x499be0
  489c51:	b9 28 cd 59 00       	mov    ecx,0x59cd28
  489c56:	eb 0a                	jmp    0x489c62
  489c58:	e8 83 ff 00 00       	call   0x499be0
  489c5d:	b9 60 cd 59 00       	mov    ecx,0x59cd60
  489c62:	89 3d 4c 2a 62 0a    	mov    DWORD PTR ds:0xa622a4c,edi
  489c68:	e8 93 7e 0d 00       	call   0x561b00
  489c6d:	8b c8                	mov    ecx,eax
  489c6f:	e8 9c c8 06 00       	call   0x4f6510
  489c74:	b9 f0 cc 59 00       	mov    ecx,0x59ccf0
  489c79:	e8 92 1e 07 00       	call   0x4fbb10
  489c7e:	84 c0                	test   al,al
  489c80:	0f 85 69 01 00 00    	jne    0x489def
  489c86:	66 c7 84 9c d8 00 00 	mov    WORD PTR [esp+ebx*4+0xd8],0x101
  489c8d:	00 01 01 
  489c90:	8b 44 24 54          	mov    eax,DWORD PTR [esp+0x54]
  489c94:	47                   	inc    edi
  489c95:	81 ff f4 01 00 00    	cmp    edi,0x1f4
  489c9b:	0f 8c bf fc ff ff    	jl     0x489960
  489ca1:	8b 5c 24 4c          	mov    ebx,DWORD PTR [esp+0x4c]

