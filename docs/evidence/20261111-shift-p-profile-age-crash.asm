# Windows x86 3.89.1; preferred base 00400000.
# Original PE SHA-256 c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d
# Offline extraction; no product execution.
# PE data: VA 0057E418 = 11h; DWORD [0057E344 + 11h*4] = 0057D915.
# Therefore switch input ASCII P (50h), minus 20h, selects VA 0057D915.

# VA 0057D716..0057D730 (exclusive end)
  57d716:	8d 43 e0             	lea    eax,[ebx-0x20]
  57d719:	83 f8 58             	cmp    eax,0x58
  57d71c:	0f 87 56 05 00 00    	ja     0x57dc78
  57d722:	0f b6 80 e8 e3 57 00 	movzx  eax,BYTE PTR [eax+0x57e3e8]
  57d729:	ff 24 85 44 e3 57 00 	jmp    DWORD PTR [eax*4+0x57e344]

# VA 0057D915..0057D929 (exclusive end)
  57d915:	e8 46 d6 f8 ff       	call   0x50af60
  57d91a:	e8 51 60 f8 ff       	call   0x503970
  57d91f:	e8 1c d6 f8 ff       	call   0x50af40
  57d924:	e9 4f 03 00 00       	jmp    0x57dc78

# VA 00503970..005039EF (exclusive end)
  503970:	55                   	push   ebp
  503971:	8b ec                	mov    ebp,esp
  503973:	83 ec 18             	sub    esp,0x18
  503976:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  50397b:	33 c5                	xor    eax,ebp
  50397d:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  503980:	0f 28 05 c0 da 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5ddac0
  503987:	8d 45 ec             	lea    eax,[ebp-0x14]
  50398a:	50                   	push   eax
  50398b:	ff 35 24 bd 5b 0a    	push   DWORD PTR ds:0xa5bbd24
  503991:	c7 05 fc ba 5b 06 00 	mov    DWORD PTR ds:0x65bbafc,0x0
  503998:	00 00 00 
  50399b:	50                   	push   eax
  50399c:	ff 35 10 bb 5b 06    	push   DWORD PTR ds:0x65bbb10
  5039a2:	0f 11 45 ec          	movups XMMWORD PTR [ebp-0x14],xmm0
  5039a6:	ff 15 04 c2 58 00    	call   DWORD PTR ds:0x58c204
  5039ac:	83 c4 10             	add    esp,0x10
  5039af:	c7 05 fc ba 5b 06 01 	mov    DWORD PTR ds:0x65bbafc,0x1
  5039b6:	00 00 00 
  5039b9:	33 d2                	xor    edx,edx
  5039bb:	b9 2c 52 78 0a       	mov    ecx,0xa78522c
  5039c0:	8a 01                	mov    al,BYTE PTR [ecx]
  5039c2:	8d 52 01             	lea    edx,[edx+0x1]
  5039c5:	81 c1 48 0c 00 00    	add    ecx,0xc48
  5039cb:	88 82 6f ef 80 0a    	mov    BYTE PTR [edx+0xa80ef6f],al
  5039d1:	81 f9 2c 76 7e 0a    	cmp    ecx,0xa7e762c
  5039d7:	7c e7                	jl     0x5039c0
  5039d9:	b9 5c 41 59 00       	mov    ecx,0x59415c
  5039de:	e8 0d 77 00 00       	call   0x50b0f0
  5039e3:	33 c9                	xor    ecx,ecx
  5039e5:	e8 c6 2c fe ff       	call   0x4e66b0
  5039ea:	e8 91 02 fd ff       	call   0x4d3c80

# VA 004E6610..004E6828 (exclusive end)
  4e6610:	a1 a8 b7 84 0a       	mov    eax,ds:0xa84b7a8
  4e6615:	40                   	inc    eax
  4e6616:	56                   	push   esi
  4e6617:	25 ff 03 00 80       	and    eax,0x800003ff
  4e661c:	79 07                	jns    0x4e6625
  4e661e:	48                   	dec    eax
  4e661f:	0d 00 fc ff ff       	or     eax,0xfffffc00
  4e6624:	40                   	inc    eax
  4e6625:	a3 a8 b7 84 0a       	mov    ds:0xa84b7a8,eax
  4e662a:	c1 e0 0a             	shl    eax,0xa
  4e662d:	68 00 04 00 00       	push   0x400
  4e6632:	6a 00                	push   0x0
  4e6634:	8d b0 b0 1e 94 0a    	lea    esi,[eax+0xa941eb0]
  4e663a:	56                   	push   esi
  4e663b:	e8 20 48 0a 00       	call   0x58ae60
  4e6640:	a1 c4 b1 72 0a       	mov    eax,ds:0xa72b1c4
  4e6645:	83 c4 0c             	add    esp,0xc
  4e6648:	48                   	dec    eax
  4e6649:	50                   	push   eax
  4e664a:	0f b6 05 b9 b1 72 0a 	movzx  eax,BYTE PTR ds:0xa72b1b9
  4e6651:	50                   	push   eax
  4e6652:	68 74 6d 5a 00       	push   0x5a6d74
  4e6657:	56                   	push   esi
  4e6658:	e8 73 aa f1 ff       	call   0x4010d0
  4e665d:	a1 c4 b1 72 0a       	mov    eax,ds:0xa72b1c4
  4e6662:	83 c4 10             	add    esp,0x10
  4e6665:	83 f8 01             	cmp    eax,0x1
  4e6668:	75 1b                	jne    0x4e6685
  4e666a:	0f b6 05 b9 b1 72 0a 	movzx  eax,BYTE PTR ds:0xa72b1b9
  4e6671:	50                   	push   eax
  4e6672:	68 b0 6d 5a 00       	push   0x5a6db0
  4e6677:	56                   	push   esi
  4e6678:	e8 53 aa f1 ff       	call   0x4010d0
  4e667d:	a1 c4 b1 72 0a       	mov    eax,ds:0xa72b1c4
  4e6682:	83 c4 0c             	add    esp,0xc
  4e6685:	83 f8 02             	cmp    eax,0x2
  4e6688:	75 16                	jne    0x4e66a0
  4e668a:	0f b6 0d b9 b1 72 0a 	movzx  ecx,BYTE PTR ds:0xa72b1b9
  4e6691:	51                   	push   ecx
  4e6692:	68 ec 6d 5a 00       	push   0x5a6dec
  4e6697:	56                   	push   esi
  4e6698:	e8 33 aa f1 ff       	call   0x4010d0
  4e669d:	83 c4 0c             	add    esp,0xc
  4e66a0:	8b c6                	mov    eax,esi
  4e66a2:	5e                   	pop    esi
  4e66a3:	c3                   	ret
  4e66a4:	cc                   	int3
  4e66a5:	cc                   	int3
  4e66a6:	cc                   	int3
  4e66a7:	cc                   	int3
  4e66a8:	cc                   	int3
  4e66a9:	cc                   	int3
  4e66aa:	cc                   	int3
  4e66ab:	cc                   	int3
  4e66ac:	cc                   	int3
  4e66ad:	cc                   	int3
  4e66ae:	cc                   	int3
  4e66af:	cc                   	int3
  4e66b0:	55                   	push   ebp
  4e66b1:	8b ec                	mov    ebp,esp
  4e66b3:	83 e4 f8             	and    esp,0xfffffff8
  4e66b6:	81 ec 74 04 00 00    	sub    esp,0x474
  4e66bc:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  4e66c1:	33 c4                	xor    eax,esp
  4e66c3:	89 84 24 70 04 00 00 	mov    DWORD PTR [esp+0x470],eax
  4e66ca:	53                   	push   ebx
  4e66cb:	56                   	push   esi
  4e66cc:	57                   	push   edi
  4e66cd:	51                   	push   ecx
  4e66ce:	68 58 02 00 00       	push   0x258
  4e66d3:	68 20 03 00 00       	push   0x320
  4e66d8:	83 ec 08             	sub    esp,0x8
  4e66db:	c7 05 5c ba 5b 06 01 	mov    DWORD PTR ds:0x65bba5c,0x1
  4e66e2:	00 00 00 
  4e66e5:	8b f9                	mov    edi,ecx
  4e66e7:	33 d2                	xor    edx,edx
  4e66e9:	b9 4c 06 59 00       	mov    ecx,0x59064c
  4e66ee:	e8 cd c0 02 00       	call   0x5127c0
  4e66f3:	83 c4 14             	add    esp,0x14
  4e66f6:	ba 68 01 00 00       	mov    edx,0x168
  4e66fb:	6a 00                	push   0x0
  4e66fd:	6a 02                	push   0x2
  4e66ff:	68 54 6d 5a 00       	push   0x5a6d54
  4e6704:	6a 7d                	push   0x7d
  4e6706:	68 c8 00 00 00       	push   0xc8
  4e670b:	8d 4a a6             	lea    ecx,[edx-0x5a]
  4e670e:	e8 5d fb 02 00       	call   0x516270
  4e6713:	83 c4 14             	add    esp,0x14
  4e6716:	ba ea 01 00 00       	mov    edx,0x1ea
  4e671b:	b9 0e 01 00 00       	mov    ecx,0x10e
  4e6720:	6a 00                	push   0x0
  4e6722:	6a 02                	push   0x2
  4e6724:	68 68 6d 5a 00       	push   0x5a6d68
  4e6729:	6a 41                	push   0x41
  4e672b:	68 c8 00 00 00       	push   0xc8
  4e6730:	e8 3b fb 02 00       	call   0x516270
  4e6735:	a1 a8 b7 84 0a       	mov    eax,ds:0xa84b7a8
  4e673a:	83 c4 14             	add    esp,0x14
  4e673d:	40                   	inc    eax
  4e673e:	25 ff 03 00 80       	and    eax,0x800003ff
  4e6743:	79 07                	jns    0x4e674c
  4e6745:	48                   	dec    eax
  4e6746:	0d 00 fc ff ff       	or     eax,0xfffffc00
  4e674b:	40                   	inc    eax
  4e674c:	a3 a8 b7 84 0a       	mov    ds:0xa84b7a8,eax
  4e6751:	c1 e0 0a             	shl    eax,0xa
  4e6754:	68 00 04 00 00       	push   0x400
  4e6759:	6a 00                	push   0x0
  4e675b:	8d b0 b0 1e 94 0a    	lea    esi,[eax+0xa941eb0]
  4e6761:	56                   	push   esi
  4e6762:	e8 f9 46 0a 00       	call   0x58ae60
  4e6767:	83 c4 0c             	add    esp,0xc
  4e676a:	68 f6 a6 72 0a       	push   0xa72a6f6
  4e676f:	68 e8 a6 72 0a       	push   0xa72a6e8
  4e6774:	68 80 c6 58 00       	push   0x58c680
  4e6779:	56                   	push   esi
  4e677a:	e8 51 a9 f1 ff       	call   0x4010d0
  4e677f:	83 c4 10             	add    esp,0x10
  4e6782:	8b ce                	mov    ecx,esi
  4e6784:	e8 a7 28 01 00       	call   0x4f9030
  4e6789:	85 ff                	test   edi,edi
  4e678b:	74 0f                	je     0x4e679c
  4e678d:	0f b6 05 b9 b1 72 0a 	movzx  eax,BYTE PTR ds:0xa72b1b9
  4e6794:	50                   	push   eax
  4e6795:	68 28 6e 5a 00       	push   0x5a6e28
  4e679a:	eb 0b                	jmp    0x4e67a7
  4e679c:	e8 6f fe ff ff       	call   0x4e6610
  4e67a1:	50                   	push   eax
  4e67a2:	68 6c 6e 5a 00       	push   0x5a6e6c
  4e67a7:	8d 84 24 80 00 00 00 	lea    eax,[esp+0x80]
  4e67ae:	50                   	push   eax
  4e67af:	e8 1c a9 f1 ff       	call   0x4010d0
  4e67b4:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  4e67b9:	83 c4 0c             	add    esp,0xc
  4e67bc:	8b 35 f8 c1 58 00    	mov    esi,DWORD PTR ds:0x58c1f8
  4e67c2:	68 8c 00 00 00       	push   0x8c
  4e67c7:	68 e6 00 00 00       	push   0xe6
  4e67cc:	68 f0 00 00 00       	push   0xf0
  4e67d1:	ff 70 04             	push   DWORD PTR [eax+0x4]
  4e67d4:	ff d6                	call   esi
  4e67d6:	8d 8c 24 88 00 00 00 	lea    ecx,[esp+0x88]
  4e67dd:	83 c4 10             	add    esp,0x10
  4e67e0:	8b d0                	mov    edx,eax
  4e67e2:	8d 59 01             	lea    ebx,[ecx+0x1]
  4e67e5:	8a 01                	mov    al,BYTE PTR [ecx]
  4e67e7:	41                   	inc    ecx
  4e67e8:	84 c0                	test   al,al
  4e67ea:	75 f9                	jne    0x4e67e5
  4e67ec:	2b cb                	sub    ecx,ebx
  4e67ee:	8d 44 24 78          	lea    eax,[esp+0x78]
  4e67f2:	6a 01                	push   0x1
  4e67f4:	52                   	push   edx
  4e67f5:	50                   	push   eax
  4e67f6:	8d 04 cd 00 00 00 00 	lea    eax,[ecx*8+0x0]
  4e67fd:	b9 90 01 00 00       	mov    ecx,0x190
  4e6802:	99                   	cdq
  4e6803:	2b c2                	sub    eax,edx
  4e6805:	ba 1e 00 00 00       	mov    edx,0x1e
  4e680a:	d1 f8                	sar    eax,1
  4e680c:	2b c8                	sub    ecx,eax
  4e680e:	e8 8d 7d 02 00       	call   0x50e5a0
  4e6813:	0f b6 05 aa b1 72 0a 	movzx  eax,BYTE PTR ds:0xa72b1aa
  4e681a:	83 c4 0c             	add    esp,0xc
  4e681d:	ba 86 01 00 00       	mov    edx,0x186
  4e6822:	50                   	push   eax
  4e6823:	68 78 6e 5a 00       	push   0x5a6e78
