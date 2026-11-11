
/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

0055d700 <.text+0x15c700>:
  55d700:	5d                   	pop    ebp
  55d701:	00 b9 01 00 00 00    	add    BYTE PTR [ecx+0x1],bh
  55d707:	e8 f4 4b 00 00       	call   0x562300
  55d70c:	ba 84 72 5d 00       	mov    edx,0x5d7284
  55d711:	33 c9                	xor    ecx,ecx
  55d713:	e8 e8 4b 00 00       	call   0x562300
  55d718:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  55d71d:	6a 01                	push   0x1
  55d71f:	68 ff 00 00 00       	push   0xff
  55d724:	68 ff 00 00 00       	push   0xff
  55d729:	68 ff 00 00 00       	push   0xff
  55d72e:	ff 70 04             	push   DWORD PTR [eax+0x4]
  55d731:	ff d6                	call   esi
  55d733:	83 c4 10             	add    esp,0x10
  55d736:	ba e0 01 00 00       	mov    edx,0x1e0
  55d73b:	b9 14 00 00 00       	mov    ecx,0x14
  55d740:	50                   	push   eax
  55d741:	68 96 00 00 00       	push   0x96
  55d746:	68 b8 01 00 00       	push   0x1b8
  55d74b:	e8 f0 13 fb ff       	call   0x50eb40
  55d750:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  55d753:	83 c4 10             	add    esp,0x10
  55d756:	33 cd                	xor    ecx,ebp
  55d758:	c7 05 d8 b8 72 0a ff 	mov    DWORD PTR ds:0xa72b8d8,0xffffffff
  55d75f:	ff ff ff 
  55d762:	5e                   	pop    esi
  55d763:	e8 46 c9 02 00       	call   0x58a0ae
  55d768:	8b e5                	mov    esp,ebp
  55d76a:	5d                   	pop    ebp
  55d76b:	c3                   	ret
  55d76c:	cc                   	int3
  55d76d:	cc                   	int3
  55d76e:	cc                   	int3
  55d76f:	cc                   	int3
  55d770:	55                   	push   ebp
  55d771:	8b ec                	mov    ebp,esp
  55d773:	83 e4 f8             	and    esp,0xfffffff8
  55d776:	81 ec dc 00 00 00    	sub    esp,0xdc
  55d77c:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  55d781:	33 c4                	xor    eax,esp
  55d783:	89 84 24 d8 00 00 00 	mov    DWORD PTR [esp+0xd8],eax
  55d78a:	8b 15 a8 97 5e 00    	mov    edx,DWORD PTR ds:0x5e97a8
  55d790:	33 c9                	xor    ecx,ecx
  55d792:	53                   	push   ebx
  55d793:	56                   	push   esi
  55d794:	57                   	push   edi
  55d795:	89 54 24 10          	mov    DWORD PTR [esp+0x10],edx
  55d799:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [eax+0x0]
  55d7a0:	8a 81 c4 10 62 0a    	mov    al,BYTE PTR [ecx+0xa6210c4]
  55d7a6:	8d 49 01             	lea    ecx,[ecx+0x1]
  55d7a9:	88 44 0c 17          	mov    BYTE PTR [esp+ecx*1+0x17],al
  55d7ad:	84 c0                	test   al,al
  55d7af:	75 ef                	jne    0x55d7a0
  55d7b1:	8b 1d f8 c1 58 00    	mov    ebx,DWORD PTR ds:0x58c1f8
  55d7b7:	83 fa 01             	cmp    edx,0x1
  55d7ba:	0f 8d ce 02 00 00    	jge    0x55da8e
  55d7c0:	a1 8c 0e 62 0a       	mov    eax,ds:0xa620e8c
  55d7c5:	85 c0                	test   eax,eax
  55d7c7:	6a 54                	push   0x54
  55d7c9:	0f 44 05 c0 10 62 0a 	cmove  eax,DWORD PTR ds:0xa6210c0
  55d7d0:	a3 8c 0e 62 0a       	mov    ds:0xa620e8c,eax
  55d7d5:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  55d7da:	68 fc 00 00 00       	push   0xfc
  55d7df:	68 fc 00 00 00       	push   0xfc
  55d7e4:	c7 05 a8 97 5e 00 00 	mov    DWORD PTR ds:0x5e97a8,0x0
  55d7eb:	00 00 00 
  55d7ee:	ff 70 04             	push   DWORD PTR [eax+0x4]
  55d7f1:	ff d3                	call   ebx
  55d7f3:	83 c4 0c             	add    esp,0xc
  55d7f6:	ba 1e 00 00 00       	mov    edx,0x1e
  55d7fb:	6a 0f                	push   0xf
  55d7fd:	68 cc 01 00 00       	push   0x1cc
  55d802:	8d 4a ec             	lea    ecx,[edx-0x14]
  55d805:	e8 76 3c fb ff       	call   0x511480
  55d80a:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  55d80f:	83 c4 0c             	add    esp,0xc
  55d812:	68 de 00 00 00       	push   0xde
  55d817:	68 c4 00 00 00       	push   0xc4
  55d81c:	68 b0 00 00 00       	push   0xb0
  55d821:	ff 70 04             	push   DWORD PTR [eax+0x4]
  55d824:	ff d3                	call   ebx
  55d826:	ba 22 00 00 00       	mov    edx,0x22
  55d82b:	6a 01                	push   0x1
  55d82d:	50                   	push   eax
  55d82e:	68 b8 72 5d 00       	push   0x5d72b8
  55d833:	8d 4a ed             	lea    ecx,[edx-0x13]
  55d836:	e8 65 0d fb ff       	call   0x50e5a0
  55d83b:	83 c4 1c             	add    esp,0x1c
  55d83e:	8d 44 24 18          	lea    eax,[esp+0x18]
  55d842:	ba 32 00 00 00       	mov    edx,0x32
  55d847:	6a 22                	push   0x22
  55d849:	50                   	push   eax
  55d84a:	68 b4 00 00 00       	push   0xb4
  55d84f:	68 cc 01 00 00       	push   0x1cc
  55d854:	8d 4a d8             	lea    ecx,[edx-0x28]
  55d857:	e8 14 86 fb ff       	call   0x515e70
  55d85c:	83 c4 10             	add    esp,0x10
  55d85f:	ba 28 11 62 0a       	mov    edx,0xa621128
  55d864:	b9 01 00 00 00       	mov    ecx,0x1
  55d869:	e8 92 4a 00 00       	call   0x562300
  55d86e:	be f0 11 62 0a       	mov    esi,0xa6211f0
  55d873:	8b d6                	mov    edx,esi
  55d875:	33 c9                	xor    ecx,ecx
  55d877:	e8 84 4a 00 00       	call   0x562300
  55d87c:	81 c6 c8 00 00 00    	add    esi,0xc8
  55d882:	81 fe 48 14 62 0a    	cmp    esi,0xa621448
  55d888:	7c e9                	jl     0x55d873
  55d88a:	6a 00                	push   0x0
  55d88c:	ba 4b 00 00 00       	mov    edx,0x4b
  55d891:	6a 00                	push   0x0
  55d893:	68 d2 00 00 00       	push   0xd2
  55d898:	68 b8 01 00 00       	push   0x1b8
  55d89d:	8d 4a c9             	lea    ecx,[edx-0x37]
  55d8a0:	e8 9b 12 fb ff       	call   0x50eb40
  55d8a5:	b9 a8 17 62 0a       	mov    ecx,0xa6217a8
  55d8aa:	83 c4 10             	add    esp,0x10
  55d8ad:	8d 51 01             	lea    edx,[ecx+0x1]
  55d8b0:	8a 01                	mov    al,BYTE PTR [ecx]
  55d8b2:	41                   	inc    ecx
  55d8b3:	84 c0                	test   al,al
  55d8b5:	75 f9                	jne    0x55d8b0
  55d8b7:	2b ca                	sub    ecx,edx
  55d8b9:	74 20                	je     0x55d8db
  55d8bb:	6a 28                	push   0x28
  55d8bd:	68 c8 72 5d 00       	push   0x5d72c8
  55d8c2:	6a 64                	push   0x64
  55d8c4:	68 cc 01 00 00       	push   0x1cc
  55d8c9:	ba eb 00 00 00       	mov    edx,0xeb
  55d8ce:	b9 0a 00 00 00       	mov    ecx,0xa
  55d8d3:	e8 98 85 fb ff       	call   0x515e70
  55d8d8:	83 c4 10             	add    esp,0x10
  55d8db:	bf 04 01 00 00       	mov    edi,0x104
  55d8e0:	be a8 17 62 0a       	mov    esi,0xa6217a8
  55d8e5:	8b c6                	mov    eax,esi
  55d8e7:	8d 50 01             	lea    edx,[eax+0x1]
  55d8ea:	66 0f 1f 44 00 00    	nop    WORD PTR [eax+eax*1+0x0]
  55d8f0:	8a 08                	mov    cl,BYTE PTR [eax]
  55d8f2:	40                   	inc    eax
  55d8f3:	84 c9                	test   cl,cl
  55d8f5:	75 f9                	jne    0x55d8f0
  55d8f7:	2b c2                	sub    eax,edx
  55d8f9:	74 69                	je     0x55d964
  55d8fb:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  55d900:	68 aa 00 00 00       	push   0xaa
  55d905:	68 e8 00 00 00       	push   0xe8
  55d90a:	68 ee 00 00 00       	push   0xee
  55d90f:	ff 70 04             	push   DWORD PTR [eax+0x4]
  55d912:	ff d3                	call   ebx
  55d914:	83 c4 10             	add    esp,0x10
  55d917:	a3 c4 ba 5b 06       	mov    ds:0x65bbac4,eax
  55d91c:	80 3e 5b             	cmp    BYTE PTR [esi],0x5b
  55d91f:	c7 05 54 ba 5b 06 01 	mov    DWORD PTR ds:0x65bba54,0x1
  55d926:	00 00 00 
  55d929:	75 15                	jne    0x55d940
  55d92b:	51                   	push   ecx
  55d92c:	50                   	push   eax
  55d92d:	56                   	push   esi
  55d92e:	8d 57 04             	lea    edx,[edi+0x4]
  55d931:	b9 14 00 00 00       	mov    ecx,0x14
  55d936:	e8 e5 0d fb ff       	call   0x50e720
  55d93b:	83 c4 0c             	add    esp,0xc
  55d93e:	eb 10                	jmp    0x55d950
  55d940:	56                   	push   esi
  55d941:	8b d7                	mov    edx,edi
  55d943:	b9 14 00 00 00       	mov    ecx,0x14
  55d948:	e8 33 6d fb ff       	call   0x514680
  55d94d:	83 c4 04             	add    esp,0x4
  55d950:	c7 05 c4 ba 5b 06 00 	mov    DWORD PTR ds:0x65bbac4,0x0
  55d957:	00 00 00 
  55d95a:	c7 05 54 ba 5b 06 00 	mov    DWORD PTR ds:0x65bba54,0x0
  55d961:	00 00 00 
  55d964:	81 c6 c8 00 00 00    	add    esi,0xc8
  55d96a:	83 c7 0f             	add    edi,0xf
  55d96d:	81 fe c8 1a 62 0a    	cmp    esi,0xa621ac8
  55d973:	0f 8c 6c ff ff ff    	jl     0x55d8e5
  55d979:	6a 00                	push   0x0
  55d97b:	6a 04                	push   0x4
  55d97d:	68 16 c6 58 00       	push   0x58c616
  55d982:	68 9b 00 00 00       	push   0x9b
  55d987:	68 cc 01 00 00       	push   0x1cc
  55d98c:	ba b8 01 00 00       	mov    edx,0x1b8
  55d991:	b9 0a 00 00 00       	mov    ecx,0xa
  55d996:	e8 d5 88 fb ff       	call   0x516270
  55d99b:	83 c4 14             	add    esp,0x14
  55d99e:	ba e0 72 5d 00       	mov    edx,0x5d72e0
  55d9a3:	b9 01 00 00 00       	mov    ecx,0x1
  55d9a8:	e8 53 49 00 00       	call   0x562300
  55d9ad:	ba 1c 73 5d 00       	mov    edx,0x5d731c
  55d9b2:	33 c9                	xor    ecx,ecx
  55d9b4:	e8 47 49 00 00       	call   0x562300
  55d9b9:	ba 58 73 5d 00       	mov    edx,0x5d7358
  55d9be:	33 c9                	xor    ecx,ecx
  55d9c0:	e8 3b 49 00 00       	call   0x562300
  55d9c5:	ba 8c 73 5d 00       	mov    edx,0x5d738c
  55d9ca:	33 c9                	xor    ecx,ecx
  55d9cc:	e8 2f 49 00 00       	call   0x562300
  55d9d1:	ba c8 73 5d 00       	mov    edx,0x5d73c8
  55d9d6:	33 c9                	xor    ecx,ecx
  55d9d8:	e8 23 49 00 00       	call   0x562300
  55d9dd:	ba 04 74 5d 00       	mov    edx,0x5d7404
  55d9e2:	33 c9                	xor    ecx,ecx
  55d9e4:	e8 17 49 00 00       	call   0x562300
  55d9e9:	ba 3c 74 5d 00       	mov    edx,0x5d743c
  55d9ee:	33 c9                	xor    ecx,ecx
  55d9f0:	e8 0b 49 00 00       	call   0x562300
  55d9f5:	ba 78 74 5d 00       	mov    edx,0x5d7478
  55d9fa:	33 c9                	xor    ecx,ecx
  55d9fc:	e8 ff 48 00 00       	call   0x562300
  55da01:	ba b0 74 5d 00       	mov    edx,0x5d74b0
  55da06:	33 c9                	xor    ecx,ecx
  55da08:	e8 f3 48 00 00       	call   0x562300
  55da0d:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  55da12:	68 e0 00 00 00       	push   0xe0
  55da17:	68 ff 00 00 00       	push   0xff
  55da1c:	68 ff 00 00 00       	push   0xff
  55da21:	ff 70 04             	push   DWORD PTR [eax+0x4]
  55da24:	ff d3                	call   ebx
  55da26:	68 e8 74 5d 00       	push   0x5d74e8
  55da2b:	ba 2b 02 00 00       	mov    edx,0x22b
  55da30:	a3 c4 ba 5b 06       	mov    ds:0x65bbac4,eax
  55da35:	b9 0f 00 00 00       	mov    ecx,0xf
  55da3a:	c7 05 54 ba 5b 06 01 	mov    DWORD PTR ds:0x65bba54,0x1
  55da41:	00 00 00 
  55da44:	e8 37 6c fb ff       	call   0x514680
  55da49:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  55da4e:	83 c4 14             	add    esp,0x14
  55da51:	6a 01                	push   0x1
  55da53:	68 aa 00 00 00       	push   0xaa
  55da58:	68 e8 00 00 00       	push   0xe8
  55da5d:	68 ee 00 00 00       	push   0xee
  55da62:	ff 70 04             	push   DWORD PTR [eax+0x4]
  55da65:	ff d3                	call   ebx
  55da67:	83 c4 10             	add    esp,0x10
  55da6a:	ba c2 01 00 00       	mov    edx,0x1c2
  55da6f:	b9 14 00 00 00       	mov    ecx,0x14
  55da74:	50                   	push   eax
  55da75:	68 c8 00 00 00       	push   0xc8
  55da7a:	68 b8 01 00 00       	push   0x1b8
  55da7f:	e8 bc 10 fb ff       	call   0x50eb40
  55da84:	8b 54 24 20          	mov    edx,DWORD PTR [esp+0x20]
  55da88:	83 c4 10             	add    esp,0x10
  55da8b:	83 fa 01             	cmp    edx,0x1
  55da8e:	0f 85 61 01 00 00    	jne    0x55dbf5
  55da94:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  55da99:	6a 54                	push   0x54
  55da9b:	68 fc 00 00 00       	push   0xfc
  55daa0:	68 fc 00 00 00       	push   0xfc
  55daa5:	ff 70 04             	push   DWORD PTR [eax+0x4]
  55daa8:	ff d3                	call   ebx
  55daaa:	68 80 00 00 00       	push   0x80
  55daaf:	ba 1e 00 00 00       	mov    edx,0x1e
  55dab4:	8b f0                	mov    esi,eax
  55dab6:	6a 00                	push   0x0
  55dab8:	6a 10                	push   0x10
  55daba:	68 cc 01 00 00       	push   0x1cc
  55dabf:	8d 4a ec             	lea    ecx,[edx-0x14]
  55dac2:	e8 39 fe fa ff       	call   0x50d900
  55dac7:	ba 1e 00 00 00       	mov    edx,0x1e
  55dacc:	c7 05 68 10 61 0a 00 	mov    DWORD PTR ds:0xa611068,0x0
  55dad3:	00 00 00 
  55dad6:	6a 2d                	push   0x2d
  55dad8:	68 d5 01 00 00       	push   0x1d5
  55dadd:	8d 4a ec             	lea    ecx,[edx-0x14]
  55dae0:	e8 5b 0a fb ff       	call   0x50e540
  55dae5:	ba 22 00 00 00       	mov    edx,0x22
  55daea:	6a 01                	push   0x1
  55daec:	56                   	push   esi
  55daed:	68 10 75 5d 00       	push   0x5d7510
  55daf2:	8d 4a ed             	lea    ecx,[edx-0x13]
  55daf5:	e8 a6 0a fb ff       	call   0x50e5a0
  55dafa:	83 c4 34             	add    esp,0x34
  55dafd:	8d 44 24 18          	lea    eax,[esp+0x18]
  55db01:	ba 32 00 00 00       	mov    edx,0x32
  55db06:	6a 08                	push   0x8
  55db08:	50                   	push   eax
  55db09:	68 96 00 00 00       	push   0x96
  55db0e:	68 cc 01 00 00       	push   0x1cc
  55db13:	8d 4a d8             	lea    ecx,[edx-0x28]
  55db16:	e8 55 83 fb ff       	call   0x515e70
  55db1b:	83 c4 10             	add    esp,0x10
  55db1e:	ba 50 14 62 0a       	mov    edx,0xa621450
  55db23:	b9 01 00 00 00       	mov    ecx,0x1
  55db28:	e8 d3 47 00 00       	call   0x562300
  55db2d:	be 18 15 62 0a       	mov    esi,0xa621518
  55db32:	8b d6                	mov    edx,esi
  55db34:	33 c9                	xor    ecx,ecx
  55db36:	e8 c5 47 00 00       	call   0x562300
  55db3b:	81 c6 c8 00 00 00    	add    esi,0xc8
  55db41:	81 fe 70 17 62 0a    	cmp    esi,0xa621770
  55db47:	7c e9                	jl     0x55db32
  55db49:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  55db4e:	6a 01                	push   0x1
  55db50:	68 ff 00 00 00       	push   0xff
  55db55:	68 ff 00 00 00       	push   0xff
  55db5a:	68 ff 00 00 00       	push   0xff
  55db5f:	ff 70 04             	push   DWORD PTR [eax+0x4]
  55db62:	ff d3                	call   ebx
  55db64:	83 c4 10             	add    esp,0x10
  55db67:	ba 50 00 00 00       	mov    edx,0x50
  55db6c:	50                   	push   eax
  55db6d:	68 c8 00 00 00       	push   0xc8
  55db72:	68 b8 01 00 00       	push   0x1b8
  55db77:	8d 4a c4             	lea    ecx,[edx-0x3c]
  55db7a:	e8 c1 0f fb ff       	call   0x50eb40
  55db7f:	6a 04                	push   0x4
  55db81:	68 16 c6 58 00       	push   0x58c616
  55db86:	6a 5f                	push   0x5f
  55db88:	68 cc 01 00 00       	push   0x1cc
  55db8d:	ba f4 01 00 00       	mov    edx,0x1f4
  55db92:	b9 0a 00 00 00       	mov    ecx,0xa
  55db97:	e8 d4 82 fb ff       	call   0x515e70
  55db9c:	83 c4 20             	add    esp,0x20
  55db9f:	ba 20 75 5d 00       	mov    edx,0x5d7520
  55dba4:	b9 01 00 00 00       	mov    ecx,0x1
  55dba9:	e8 52 47 00 00       	call   0x562300
  55dbae:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  55dbb3:	6a 01                	push   0x1
  55dbb5:	68 aa 00 00 00       	push   0xaa
  55dbba:	68 e8 00 00 00       	push   0xe8
  55dbbf:	68 ee 00 00 00       	push   0xee
  55dbc4:	ff 70 04             	push   DWORD PTR [eax+0x4]
  55dbc7:	ff d3                	call   ebx
  55dbc9:	83 c4 10             	add    esp,0x10
  55dbcc:	ba 12 02 00 00       	mov    edx,0x212
  55dbd1:	b9 14 00 00 00       	mov    ecx,0x14
  55dbd6:	50                   	push   eax
  55dbd7:	68 c8 00 00 00       	push   0xc8
  55dbdc:	68 b8 01 00 00       	push   0x1b8
  55dbe1:	e8 5a 0f fb ff       	call   0x50eb40
  55dbe6:	a1 a4 17 62 0a       	mov    eax,ds:0xa6217a4
  55dbeb:	83 c4 10             	add    esp,0x10
  55dbee:	a3 8c 0e 62 0a       	mov    ds:0xa620e8c,eax
  55dbf3:	eb 05                	jmp    0x55dbfa
  55dbf5:	a1 8c 0e 62 0a       	mov    eax,ds:0xa620e8c
  55dbfa:	83 f8 0e             	cmp    eax,0xe
  55dbfd:	75 05                	jne    0x55dc04
  55dbff:	e8 bc f6 ff ff       	call   0x55d2c0
  55dc04:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  55dc09:	68 e0 00 00 00       	push   0xe0
  55dc0e:	68 ff 00 00 00       	push   0xff
  55dc13:	68 ff 00 00 00       	push   0xff
  55dc18:	ff 70 04             	push   DWORD PTR [eax+0x4]
  55dc1b:	ff d3                	call   ebx
  55dc1d:	68 5c 75 5d 00       	push   0x5d755c
  55dc22:	ba 3a 02 00 00       	mov    edx,0x23a
  55dc27:	a3 c4 ba 5b 06       	mov    ds:0x65bbac4,eax
  55dc2c:	b9 0f 00 00 00       	mov    ecx,0xf
  55dc31:	c7 05 54 ba 5b 06 01 	mov    DWORD PTR ds:0x65bba54,0x1
  55dc38:	00 00 00 
  55dc3b:	e8 40 6a fb ff       	call   0x514680
  55dc40:	8b 8c 24 f8 00 00 00 	mov    ecx,DWORD PTR [esp+0xf8]
  55dc47:	83 c4 14             	add    esp,0x14
  55dc4a:	c7 05 c4 ba 5b 06 00 	mov    DWORD PTR ds:0x65bbac4,0x0
  55dc51:	00 00 00 
  55dc54:	c7 05 54 ba 5b 06 00 	mov    DWORD PTR ds:0x65bba54,0x0
  55dc5b:	00 00 00 
  55dc5e:	5f                   	pop    edi
  55dc5f:	5e                   	pop    esi
  55dc60:	5b                   	pop    ebx
  55dc61:	33 cc                	xor    ecx,esp
  55dc63:	e8 46 c4 02 00       	call   0x58a0ae
  55dc68:	8b e5                	mov    esp,ebp
  55dc6a:	5d                   	pop    ebp
  55dc6b:	c3                   	ret
  55dc6c:	cc                   	int3
  55dc6d:	cc                   	int3
  55dc6e:	cc                   	int3
  55dc6f:	cc                   	int3
  55dc70:	55                   	push   ebp
  55dc71:	8b ec                	mov    ebp,esp
  55dc73:	81 ec 84 04 00 00    	sub    esp,0x484
  55dc79:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  55dc7e:	33 c5                	xor    eax,ebp
  55dc80:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  55dc83:	53                   	push   ebx
  55dc84:	56                   	push   esi
  55dc85:	33 f6                	xor    esi,esi
  55dc87:	b9 7c d5 59 00       	mov    ecx,0x59d57c
  55dc8c:	57                   	push   edi
  55dc8d:	89 35 d8 bc 5b 06    	mov    DWORD PTR ds:0x65bbcd8,esi
  55dc93:	e8 58 d4 fa ff       	call   0x50b0f0
  55dc98:	33 d2                	xor    edx,edx
  55dc9a:	b9 2c 52 78 0a       	mov    ecx,0xa78522c
  55dc9f:	90                   	nop
  55dca0:	8a 01                	mov    al,BYTE PTR [ecx]
  55dca2:	8d 52 01             	lea    edx,[edx+0x1]
  55dca5:	81 c1 48 0c 00 00    	add    ecx,0xc48
  55dcab:	88 82 6f ef 80 0a    	mov    BYTE PTR [edx+0xa80ef6f],al
  55dcb1:	81 f9 2c 76 7e 0a    	cmp    ecx,0xa7e762c
  55dcb7:	7c e7                	jl     0x55dca0
  55dcb9:	b9 5c 41 59 00       	mov    ecx,0x59415c
  55dcbe:	e8 2d d4 fa ff       	call   0x50b0f0
  55dcc3:	83 3d d8 b8 72 0a ff 	cmp    DWORD PTR ds:0xa72b8d8,0xffffffff
  55dcca:	75 4e                	jne    0x55dd1a
  55dccc:	b1 01                	mov    cl,0x1
  55dcce:	e8 6d 30 eb ff       	call   0x410d40
  55dcd3:	b9 7c d5 59 00       	mov    ecx,0x59d57c
  55dcd8:	c7 05 d8 bc 5b 06 01 	mov    DWORD PTR ds:0x65bbcd8,0x1
  55dcdf:	00 00 00 
  55dce2:	e8 79 d3 fa ff       	call   0x50b060
  55dce7:	33 d2                	xor    edx,edx
  55dce9:	b9 2c 52 78 0a       	mov    ecx,0xa78522c
  55dcee:	66 90                	xchg   ax,ax
  55dcf0:	8a 82 70 ef 80 0a    	mov    al,BYTE PTR [edx+0xa80ef70]
  55dcf6:	8d 52 01             	lea    edx,[edx+0x1]
  55dcf9:	88 01                	mov    BYTE PTR [ecx],al
  55dcfb:	81 c1 48 0c 00 00    	add    ecx,0xc48
  55dd01:	81 f9 2c 76 7e 0a    	cmp    ecx,0xa7e762c
  55dd07:	7c e7                	jl     0x55dcf0
  55dd09:	5f                   	pop    edi
  55dd0a:	5e                   	pop    esi
  55dd0b:	5b                   	pop    ebx
  55dd0c:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  55dd0f:	33 cd                	xor    ecx,ebp
  55dd11:	e8 98 c3 02 00       	call   0x58a0ae
  55dd16:	8b e5                	mov    esp,ebp
  55dd18:	5d                   	pop    ebp
  55dd19:	c3                   	ret
  55dd1a:	68 90 3c 78 0a       	push   0xa783c90
  55dd1f:	8d 85 90 fb ff ff    	lea    eax,[ebp-0x470]
  55dd25:	68 10 70 5d 00       	push   0x5d7010
  55dd2a:	50                   	push   eax
  55dd2b:	e8 a0 33 ea ff       	call   0x4010d0
  55dd30:	83 c4 0c             	add    esp,0xc
  55dd33:	8d 85 90 fb ff ff    	lea    eax,[ebp-0x470]
  55dd39:	68 f8 f1 58 00       	push   0x58f1f8
  55dd3e:	50                   	push   eax
  55dd3f:	ff 15 78 c4 58 00    	call   DWORD PTR ds:0x58c478
  55dd45:	8b f8                	mov    edi,eax
  55dd47:	83 c4 08             	add    esp,0x8
  55dd4a:	85 ff                	test   edi,edi
  55dd4c:	75 16                	jne    0x55dd64
  55dd4e:	e8 6d d4 fa ff       	call   0x50b1c0
  55dd53:	5f                   	pop    edi
  55dd54:	5e                   	pop    esi
  55dd55:	5b                   	pop    ebx
  55dd56:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  55dd59:	33 cd                	xor    ecx,ebp
  55dd5b:	e8 4e c3 02 00       	call   0x58a0ae
  55dd60:	8b e5                	mov    esp,ebp
  55dd62:	5d                   	pop    ebp
  55dd63:	c3                   	ret
  55dd64:	b9 7c d5 59 00       	mov    ecx,0x59d57c
  55dd69:	89 35 d8 bc 5b 06    	mov    DWORD PTR ds:0x65bbcd8,esi
  55dd6f:	e8 7c d3 fa ff       	call   0x50b0f0
  55dd74:	0f 28 05 c0 da 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5ddac0
  55dd7b:	8d 85 80 fb ff ff    	lea    eax,[ebp-0x480]
  55dd81:	50                   	push   eax
  55dd82:	ff 35 14 20 5c 0a    	push   DWORD PTR ds:0xa5c2014
  55dd88:	0f 11 85 80 fb ff ff 	movups XMMWORD PTR [ebp-0x480],xmm0
  55dd8f:	50                   	push   eax
  55dd90:	ff 35 10 bb 5b 06    	push   DWORD PTR ds:0x65bbb10
  55dd96:	ff 15 04 c2 58 00    	call   DWORD PTR ds:0x58c204
  55dd9c:	e8 4f dc fa ff       	call   0x50b9f0
  55dda1:	83 c4 0c             	add    esp,0xc
  55dda4:	33 d2                	xor    edx,edx
  55dda6:	b9 74 fa 58 00       	mov    ecx,0x58fa74
  55ddab:	68 58 02 00 00       	push   0x258
  55ddb0:	68 20 03 00 00       	push   0x320
  55ddb5:	83 ec 08             	sub    esp,0x8
  55ddb8:	e8 03 4a fb ff       	call   0x5127c0
  55ddbd:	83 c4 14             	add    esp,0x14
  55ddc0:	b9 b8 9e 5a 00       	mov    ecx,0x5a9eb8
  55ddc5:	e8 b6 b1 f9 ff       	call   0x4f8f80
  55ddca:	6a 00                	push   0x0
  55ddcc:	6a 10                	push   0x10
  55ddce:	68 7c 75 5d 00       	push   0x5d757c
  55ddd3:	68 30 02 00 00       	push   0x230
  55ddd8:	68 ff 00 00 00       	push   0xff
  55dddd:	ba 1e 00 00 00       	mov    edx,0x1e
  55dde2:	b9 17 02 00 00       	mov    ecx,0x217
  55dde7:	e8 84 84 fb ff       	call   0x516270
  55ddec:	83 c4 14             	add    esp,0x14
  55ddef:	57                   	push   edi
  55ddf0:	6a 01                	push   0x1
  55ddf2:	68 08 0a 00 00       	push   0xa08
  55ddf7:	68 c0 10 62 0a       	push   0xa6210c0
  55ddfc:	ff 15 a8 c4 58 00    	call   DWORD PTR ds:0x58c4a8
  55de02:	57                   	push   edi
  55de03:	ff 15 e0 c4 58 00    	call   DWORD PTR ds:0x58c4e0
  55de09:	83 c4 14             	add    esp,0x14
  55de0c:	85 c0                	test   eax,eax
  55de0e:	0f 85 19 01 00 00    	jne    0x55df2d
  55de14:	8d 58 3c             	lea    ebx,[eax+0x3c]
  55de17:	66 0f 1f 84 00 00 00 	nop    WORD PTR [eax+eax*1+0x0]
  55de1e:	00 00 
  55de20:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  55de25:	68 8c 00 00 00       	push   0x8c
  55de2a:	68 e6 00 00 00       	push   0xe6
  55de2f:	68 f0 00 00 00       	push   0xf0
  55de34:	ff 70 04             	push   DWORD PTR [eax+0x4]
  55de37:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  55de3d:	83 c4 10             	add    esp,0x10
  55de40:	a3 c4 ba 5b 06       	mov    ds:0x65bbac4,eax
  55de45:	39 35 d8 b8 72 0a    	cmp    DWORD PTR ds:0xa72b8d8,esi
  55de4b:	b0 20                	mov    al,0x20
  55de4d:	0f b6 c8             	movzx  ecx,al
  55de50:	ba 78 00 00 00       	mov    edx,0x78
  55de55:	0f 4f ca             	cmovg  ecx,edx
  55de58:	c7 05 54 ba 5b 06 01 	mov    DWORD PTR ds:0x65bba54,0x1
  55de5f:	00 00 00 
  55de62:	89 8d 7c fb ff ff    	mov    DWORD PTR [ebp-0x484],ecx
  55de68:	3b 35 d8 b8 72 0a    	cmp    esi,DWORD PTR ds:0xa72b8d8
  55de6e:	75 49                	jne    0x55deb9
  55de70:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  55de75:	68 de 00 00 00       	push   0xde
  55de7a:	68 c4 00 00 00       	push   0xc4
  55de7f:	68 b0 00 00 00       	push   0xb0
  55de84:	ff 70 04             	push   DWORD PTR [eax+0x4]
  55de87:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  55de8d:	a3 c4 ba 5b 06       	mov    ds:0x65bbac4,eax
  55de92:	83 c4 10             	add    esp,0x10
  55de95:	a1 48 14 62 0a       	mov    eax,ds:0xa621448
  55de9a:	b9 58 00 00 00       	mov    ecx,0x58
  55de9f:	83 3d a8 97 5e 00 01 	cmp    DWORD PTR ds:0x5e97a8,0x1
  55dea6:	a3 d4 b8 72 0a       	mov    ds:0xa72b8d4,eax
  55deab:	8b 85 7c fb ff ff    	mov    eax,DWORD PTR [ebp-0x484]
  55deb1:	0f b6 c0             	movzx  eax,al
  55deb4:	0f 44 c1             	cmove  eax,ecx
  55deb7:	8a c8                	mov    cl,al
  55deb9:	68 c4 10 62 0a       	push   0xa6210c4
  55debe:	0f b6 c1             	movzx  eax,cl
  55dec1:	50                   	push   eax
  55dec2:	8d 45 90             	lea    eax,[ebp-0x70]
  55dec5:	68 08 5a 59 00       	push   0x595a08
  55deca:	50                   	push   eax
  55decb:	e8 00 32 ea ff       	call   0x4010d0
  55ded0:	8d 45 90             	lea    eax,[ebp-0x70]
  55ded3:	8b d3                	mov    edx,ebx
  55ded5:	50                   	push   eax
  55ded6:	b9 1c 02 00 00       	mov    ecx,0x21c
  55dedb:	e8 a0 67 fb ff       	call   0x514680
  55dee0:	83 c4 14             	add    esp,0x14
  55dee3:	c7 05 54 ba 5b 06 00 	mov    DWORD PTR ds:0x65bba54,0x0
  55deea:	00 00 00 
  55deed:	c7 05 c4 ba 5b 06 00 	mov    DWORD PTR ds:0x65bbac4,0x0
  55def4:	00 00 00 
  55def7:	3b 35 d8 b8 72 0a    	cmp    esi,DWORD PTR ds:0xa72b8d8
  55defd:	75 05                	jne    0x55df04
  55deff:	e8 6c f8 ff ff       	call   0x55d770
  55df04:	57                   	push   edi
  55df05:	6a 01                	push   0x1
  55df07:	68 08 0a 00 00       	push   0xa08
  55df0c:	68 c0 10 62 0a       	push   0xa6210c0
  55df11:	46                   	inc    esi
  55df12:	83 c3 14             	add    ebx,0x14
  55df15:	ff 15 a8 c4 58 00    	call   DWORD PTR ds:0x58c4a8
  55df1b:	57                   	push   edi
  55df1c:	ff 15 e0 c4 58 00    	call   DWORD PTR ds:0x58c4e0
  55df22:	83 c4 14             	add    esp,0x14
  55df25:	85 c0                	test   eax,eax
  55df27:	0f 84 f3 fe ff ff    	je     0x55de20
  55df2d:	57                   	push   edi
  55df2e:	ff 15 b4 c4 58 00    	call   DWORD PTR ds:0x58c4b4
  55df34:	83 c4 04             	add    esp,0x4
  55df37:	e8 e4 d7 fa ff       	call   0x50b720
  55df3c:	0f 1f 40 00          	nop    DWORD PTR [eax+0x0]
  55df40:	e8 ab 5c f7 ff       	call   0x4d3bf0
  55df45:	83 f8 1b             	cmp    eax,0x1b
  55df48:	75 f6                	jne    0x55df40
  55df4a:	e8 81 fb fa ff       	call   0x50dad0
  55df4f:	b9 7c d5 59 00       	mov    ecx,0x59d57c
  55df54:	c7 05 d8 bc 5b 06 01 	mov    DWORD PTR ds:0x65bbcd8,0x1
  55df5b:	00 00 00 
  55df5e:	e8 fd d0 fa ff       	call   0x50b060
  55df63:	e8 58 d2 fa ff       	call   0x50b1c0
  55df68:	8b 15 d8 b8 72 0a    	mov    edx,DWORD PTR ds:0xa72b8d8
  55df6e:	33 c9                	xor    ecx,ecx
  55df70:	83 3d a8 97 5e 00 01 	cmp    DWORD PTR ds:0x5e97a8,0x1
  55df77:	0f 94 c1             	sete   cl
  55df7a:	33 c0                	xor    eax,eax
  55df7c:	83 fa ff             	cmp    edx,0xffffffff
  55df7f:	0f 95 c0             	setne  al
  55df82:	85 c8                	test   eax,ecx
  55df84:	74 25                	je     0x55dfab
  55df86:	42                   	inc    edx
  55df87:	c7 05 d4 b8 72 0a 00 	mov    DWORD PTR ds:0xa72b8d4,0x0
  55df8e:	00 00 00 
  55df91:	b9 98 75 5d 00       	mov    ecx,0x5d7598
  55df96:	89 15 d8 b8 72 0a    	mov    DWORD PTR ds:0xa72b8d8,edx
  55df9c:	c7 05 a8 97 5e 00 ff 	mov    DWORD PTR ds:0x5e97a8,0xffffffff
  55dfa3:	ff ff ff 
  55dfa6:	e8 65 85 f9 ff       	call   0x4f6510
  55dfab:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  55dfae:	5f                   	pop    edi
  55dfaf:	5e                   	pop    esi
  55dfb0:	33 cd                	xor    ecx,ebp
  55dfb2:	5b                   	pop    ebx
  55dfb3:	e8 f6 c0 02 00       	call   0x58a0ae
  55dfb8:	8b e5                	mov    esp,ebp
  55dfba:	5d                   	pop    ebp
  55dfbb:	c3                   	ret
  55dfbc:	cc                   	int3
  55dfbd:	cc                   	int3
  55dfbe:	cc                   	int3
  55dfbf:	cc                   	int3
  55dfc0:	a1 a8 b7 84 0a       	mov    eax,ds:0xa84b7a8
  55dfc5:	40                   	inc    eax
  55dfc6:	56                   	push   esi
  55dfc7:	25 ff 03 00 80       	and    eax,0x800003ff
  55dfcc:	79 07                	jns    0x55dfd5
  55dfce:	48                   	dec    eax
  55dfcf:	0d 00 fc ff ff       	or     eax,0xfffffc00
  55dfd4:	40                   	inc    eax
  55dfd5:	a3 a8 b7 84 0a       	mov    ds:0xa84b7a8,eax
  55dfda:	c1 e0 0a             	shl    eax,0xa
  55dfdd:	68 00 04 00 00       	push   0x400
  55dfe2:	6a 00                	push   0x0
  55dfe4:	8d b0 b0 1e 94 0a    	lea    esi,[eax+0xa941eb0]
  55dfea:	56                   	push   esi
  55dfeb:	e8 70 ce 02 00       	call   0x58ae60
  55dff0:	68 f6 a6 72 0a       	push   0xa72a6f6
  55dff5:	68 e8 a6 72 0a       	push   0xa72a6e8
  55dffa:	68 80 c6 58 00       	push   0x58c680
  55dfff:	56                   	push   esi
  55e000:	e8 cb 30 ea ff       	call   0x4010d0
  55e005:	83 c4 1c             	add    esp,0x1c
  55e008:	8b c6                	mov    eax,esi
  55e00a:	5e                   	pop    esi
  55e00b:	c3                   	ret
  55e00c:	cc                   	int3
  55e00d:	cc                   	int3
  55e00e:	cc                   	int3
  55e00f:	cc                   	int3
  55e010:	55                   	push   ebp
  55e011:	8b ec                	mov    ebp,esp
  55e013:	81 ec 08 04 00 00    	sub    esp,0x408
  55e019:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  55e01e:	33 c5                	xor    eax,ebp
  55e020:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  55e023:	56                   	push   esi
  55e024:	57                   	push   edi
  55e025:	bf 01 00 00 00       	mov    edi,0x1
  55e02a:	be 04 a4 5e 00       	mov    esi,0x5ea404
  55e02f:	90                   	nop
  55e030:	57                   	push   edi
  55e031:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  55e037:	68 ac 76 5d 00       	push   0x5d76ac
  55e03c:	50                   	push   eax
  55e03d:	e8 8e 30 ea ff       	call   0x4010d0
  55e042:	83 c4 0c             	add    esp,0xc
  55e045:	8d 8d f8 fb ff ff    	lea    ecx,[ebp-0x408]
  55e04b:	e8 b0 3a 00 00       	call   0x561b00
  55e050:	8b d6                	mov    edx,esi
  55e052:	2b d0                	sub    edx,eax
  55e054:	8a 08                	mov    cl,BYTE PTR [eax]
  55e056:	8d 40 01             	lea    eax,[eax+0x1]
  55e059:	88 4c 02 ff          	mov    BYTE PTR [edx+eax*1-0x1],cl
  55e05d:	84 c9                	test   cl,cl
  55e05f:	75 f3                	jne    0x55e054
  55e061:	83 c6 64             	add    esi,0x64
  55e064:	47                   	inc    edi
  55e065:	81 fe b4 a8 5e 00    	cmp    esi,0x5ea8b4
  55e06b:	7c c3                	jl     0x55e030
  55e06d:	b9 bc 76 5d 00       	mov    ecx,0x5d76bc
  55e072:	e8 89 3a 00 00       	call   0x561b00
  55e077:	ba 90 0a 6d 0a       	mov    edx,0xa6d0a90
  55e07c:	2b d0                	sub    edx,eax
  55e07e:	66 90                	xchg   ax,ax
  55e080:	8a 08                	mov    cl,BYTE PTR [eax]
  55e082:	8d 40 01             	lea    eax,[eax+0x1]
  55e085:	88 4c 02 ff          	mov    BYTE PTR [edx+eax*1-0x1],cl
  55e089:	84 c9                	test   cl,cl
  55e08b:	75 f3                	jne    0x55e080
  55e08d:	b9 d4 76 5d 00       	mov    ecx,0x5d76d4
  55e092:	e8 69 3a 00 00       	call   0x561b00
  55e097:	ba 60 0b 6d 0a       	mov    edx,0xa6d0b60
  55e09c:	2b d0                	sub    edx,eax
  55e09e:	66 90                	xchg   ax,ax
  55e0a0:	8a 08                	mov    cl,BYTE PTR [eax]
  55e0a2:	8d 40 01             	lea    eax,[eax+0x1]
  55e0a5:	88 4c 02 ff          	mov    BYTE PTR [edx+eax*1-0x1],cl
  55e0a9:	84 c9                	test   cl,cl
  55e0ab:	75 f3                	jne    0x55e0a0
  55e0ad:	b9 e8 76 5d 00       	mov    ecx,0x5d76e8
  55e0b2:	e8 49 3a 00 00       	call   0x561b00
  55e0b7:	ba c8 0b 6d 0a       	mov    edx,0xa6d0bc8
  55e0bc:	2b d0                	sub    edx,eax
  55e0be:	66 90                	xchg   ax,ax
  55e0c0:	8a 08                	mov    cl,BYTE PTR [eax]
  55e0c2:	8d 40 01             	lea    eax,[eax+0x1]
  55e0c5:	88 4c 02 ff          	mov    BYTE PTR [edx+eax*1-0x1],cl
  55e0c9:	84 c9                	test   cl,cl
  55e0cb:	75 f3                	jne    0x55e0c0
  55e0cd:	b9 fc 76 5d 00       	mov    ecx,0x5d76fc
  55e0d2:	e8 29 3a 00 00       	call   0x561b00
  55e0d7:	ba 28 0a 6d 0a       	mov    edx,0xa6d0a28
  55e0dc:	2b d0                	sub    edx,eax
  55e0de:	66 90                	xchg   ax,ax
  55e0e0:	8a 08                	mov    cl,BYTE PTR [eax]
  55e0e2:	8d 40 01             	lea    eax,[eax+0x1]
  55e0e5:	88 4c 02 ff          	mov    BYTE PTR [edx+eax*1-0x1],cl
  55e0e9:	84 c9                	test   cl,cl
  55e0eb:	75 f3                	jne    0x55e0e0
  55e0ed:	b9 10 77 5d 00       	mov    ecx,0x5d7710
  55e0f2:	e8 09 3a 00 00       	call   0x561b00
  55e0f7:	ba f8 0a 6d 0a       	mov    edx,0xa6d0af8
  55e0fc:	2b d0                	sub    edx,eax
  55e0fe:	66 90                	xchg   ax,ax
  55e100:	8a 08                	mov    cl,BYTE PTR [eax]
  55e102:	8d 40 01             	lea    eax,[eax+0x1]
  55e105:	88 4c 02 ff          	mov    BYTE PTR [edx+eax*1-0x1],cl
  55e109:	84 c9                	test   cl,cl
  55e10b:	75 f3                	jne    0x55e100
  55e10d:	b9 28 77 5d 00       	mov    ecx,0x5d7728
  55e112:	e8 e9 39 00 00       	call   0x561b00
  55e117:	ba e4 27 62 0a       	mov    edx,0xa6227e4
  55e11c:	2b d0                	sub    edx,eax
  55e11e:	66 90                	xchg   ax,ax
  55e120:	8a 08                	mov    cl,BYTE PTR [eax]
  55e122:	8d 40 01             	lea    eax,[eax+0x1]
  55e125:	88 4c 02 ff          	mov    BYTE PTR [edx+eax*1-0x1],cl
  55e129:	84 c9                	test   cl,cl
  55e12b:	75 f3                	jne    0x55e120
  55e12d:	b9 3c 77 5d 00       	mov    ecx,0x5d773c
  55e132:	e8 c9 39 00 00       	call   0x561b00
  55e137:	ba f4 0f 62 0a       	mov    edx,0xa620ff4
  55e13c:	2b d0                	sub    edx,eax
  55e13e:	66 90                	xchg   ax,ax
