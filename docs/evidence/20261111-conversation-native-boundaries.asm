  5339b0:	55                   	push   ebp
  5339b1:	8b ec                	mov    ebp,esp
  5339b3:	81 ec 14 08 00 00    	sub    esp,0x814
  5339b9:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  5339be:	33 c5                	xor    eax,ebp
  5339c0:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  5339c3:	53                   	push   ebx
  5339c4:	56                   	push   esi
  5339c5:	57                   	push   edi
  5339c6:	8b f9                	mov    edi,ecx
  5339c8:	8b d7                	mov    edx,edi
  5339ca:	89 bd f4 f7 ff ff    	mov    DWORD PTR [ebp-0x80c],edi
  5339d0:	8d 4a 01             	lea    ecx,[edx+0x1]
  5339d3:	8a 02                	mov    al,BYTE PTR [edx]
  5339d5:	42                   	inc    edx
  5339d6:	84 c0                	test   al,al
  5339d8:	75 f9                	jne    0x5339d3
  5339da:	2b d1                	sub    edx,ecx
  5339dc:	0f 84 b8 01 00 00    	je     0x533b9a
  5339e2:	8b cf                	mov    ecx,edi
  5339e4:	88 85 f8 fb ff ff    	mov    BYTE PTR [ebp-0x408],al
  5339ea:	33 db                	xor    ebx,ebx
  5339ec:	8d 51 01             	lea    edx,[ecx+0x1]
  5339ef:	90                   	nop
  5339f0:	8a 01                	mov    al,BYTE PTR [ecx]
  5339f2:	41                   	inc    ecx
  5339f3:	84 c0                	test   al,al
  5339f5:	75 f9                	jne    0x5339f0
  5339f7:	2b ca                	sub    ecx,edx
  5339f9:	0f 84 25 01 00 00    	je     0x533b24
  5339ff:	90                   	nop
  533a00:	0f b6 04 1f          	movzx  eax,BYTE PTR [edi+ebx*1]
  533a04:	50                   	push   eax
  533a05:	8d 85 f8 f7 ff ff    	lea    eax,[ebp-0x808]
  533a0b:	68 dc d6 58 00       	push   0x58d6dc
  533a10:	50                   	push   eax
  533a11:	e8 ba d6 ec ff       	call   0x4010d0
  533a16:	8d 95 f8 f7 ff ff    	lea    edx,[ebp-0x808]
  533a1c:	83 c4 0c             	add    esp,0xc
  533a1f:	8b f2                	mov    esi,edx
  533a21:	8a 02                	mov    al,BYTE PTR [edx]
  533a23:	42                   	inc    edx
  533a24:	84 c0                	test   al,al
  533a26:	75 f9                	jne    0x533a21
  533a28:	8d bd f8 fb ff ff    	lea    edi,[ebp-0x408]
  533a2e:	2b d6                	sub    edx,esi
  533a30:	4f                   	dec    edi
  533a31:	8a 47 01             	mov    al,BYTE PTR [edi+0x1]
  533a34:	47                   	inc    edi
  533a35:	84 c0                	test   al,al
  533a37:	75 f8                	jne    0x533a31
  533a39:	8b ca                	mov    ecx,edx
  533a3b:	c1 e9 02             	shr    ecx,0x2
  533a3e:	f3 a5                	rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
  533a40:	8b ca                	mov    ecx,edx
  533a42:	83 e1 03             	and    ecx,0x3
  533a45:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
  533a47:	8b bd f4 f7 ff ff    	mov    edi,DWORD PTR [ebp-0x80c]
  533a4d:	0f b6 04 1f          	movzx  eax,BYTE PTR [edi+ebx*1]
  533a51:	50                   	push   eax
  533a52:	68 a8 16 5b 00       	push   0x5b16a8
  533a57:	ff 15 48 c3 58 00    	call   DWORD PTR ds:0x58c348
  533a5d:	83 c4 08             	add    esp,0x8
  533a60:	85 c0                	test   eax,eax
  533a62:	0f 84 a5 00 00 00    	je     0x533b0d
  533a68:	80 7c 1f 01 20       	cmp    BYTE PTR [edi+ebx*1+0x1],0x20
  533a6d:	0f 84 9a 00 00 00    	je     0x533b0d
  533a73:	8d 8d f8 fb ff ff    	lea    ecx,[ebp-0x408]
  533a79:	8d 51 01             	lea    edx,[ecx+0x1]
  533a7c:	0f 1f 40 00          	nop    DWORD PTR [eax+0x0]
  533a80:	8a 01                	mov    al,BYTE PTR [ecx]
  533a82:	41                   	inc    ecx
  533a83:	84 c0                	test   al,al
  533a85:	75 f9                	jne    0x533a80
  533a87:	8b 35 a0 97 5e 00    	mov    esi,DWORD PTR ds:0x5e97a0
  533a8d:	2b ca                	sub    ecx,edx
  533a8f:	8b 15 98 97 5e 00    	mov    edx,DWORD PTR ds:0x5e9798
  533a95:	8d 04 ce             	lea    eax,[esi+ecx*8]
  533a98:	3d 2b 01 00 00       	cmp    eax,0x12b
  533a9d:	7e 14                	jle    0x533ab3
  533a9f:	be 0f 00 00 00       	mov    esi,0xf
  533aa4:	83 c2 0a             	add    edx,0xa
  533aa7:	89 35 a0 97 5e 00    	mov    DWORD PTR ds:0x5e97a0,esi
  533aad:	89 15 98 97 5e 00    	mov    DWORD PTR ds:0x5e9798,edx
  533ab3:	6a 00                	push   0x0
  533ab5:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  533abb:	8b ce                	mov    ecx,esi
  533abd:	6a 00                	push   0x0
  533abf:	50                   	push   eax
  533ac0:	e8 db aa fd ff       	call   0x50e5a0
  533ac5:	8d 8d f8 fb ff ff    	lea    ecx,[ebp-0x408]
  533acb:	83 c4 0c             	add    esp,0xc
  533ace:	8d 51 01             	lea    edx,[ecx+0x1]
  533ad1:	8a 01                	mov    al,BYTE PTR [ecx]
  533ad3:	41                   	inc    ecx
  533ad4:	84 c0                	test   al,al
  533ad6:	75 f9                	jne    0x533ad1
  533ad8:	a1 a0 97 5e 00       	mov    eax,ds:0x5e97a0
  533add:	2b ca                	sub    ecx,edx
  533adf:	68 00 04 00 00       	push   0x400
  533ae4:	6a 00                	push   0x0
  533ae6:	8d 04 c8             	lea    eax,[eax+ecx*8]
  533ae9:	a3 a0 97 5e 00       	mov    ds:0x5e97a0,eax
  533aee:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  533af4:	50                   	push   eax
  533af5:	e8 66 73 05 00       	call   0x58ae60
  533afa:	83 c4 0c             	add    esp,0xc
  533afd:	6a 03                	push   0x3
  533aff:	ff 15 68 c2 58 00    	call   DWORD PTR ds:0x58c268
  533b05:	83 c4 04             	add    esp,0x4
  533b08:	e8 13 7c fd ff       	call   0x50b720
  533b0d:	8b c7                	mov    eax,edi
  533b0f:	43                   	inc    ebx
  533b10:	8d 50 01             	lea    edx,[eax+0x1]
  533b13:	8a 08                	mov    cl,BYTE PTR [eax]
  533b15:	40                   	inc    eax
  533b16:	84 c9                	test   cl,cl
  533b18:	75 f9                	jne    0x533b13
  533b1a:	2b c2                	sub    eax,edx
  533b1c:	3b d8                	cmp    ebx,eax
  533b1e:	0f 82 dc fe ff ff    	jb     0x533a00
  533b24:	8d 8d f8 fb ff ff    	lea    ecx,[ebp-0x408]
  533b2a:	8d 51 01             	lea    edx,[ecx+0x1]
  533b2d:	0f 1f 00             	nop    DWORD PTR [eax]
  533b30:	8a 01                	mov    al,BYTE PTR [ecx]
  533b32:	41                   	inc    ecx
  533b33:	84 c0                	test   al,al
  533b35:	75 f9                	jne    0x533b30
  533b37:	8b 35 a0 97 5e 00    	mov    esi,DWORD PTR ds:0x5e97a0
  533b3d:	2b ca                	sub    ecx,edx
  533b3f:	8b 15 98 97 5e 00    	mov    edx,DWORD PTR ds:0x5e9798
  533b45:	8d 04 ce             	lea    eax,[esi+ecx*8]
  533b48:	3d 2b 01 00 00       	cmp    eax,0x12b
  533b4d:	7e 14                	jle    0x533b63
  533b4f:	be 0f 00 00 00       	mov    esi,0xf
  533b54:	83 c2 0a             	add    edx,0xa
  533b57:	89 35 a0 97 5e 00    	mov    DWORD PTR ds:0x5e97a0,esi
  533b5d:	89 15 98 97 5e 00    	mov    DWORD PTR ds:0x5e9798,edx
  533b63:	6a 00                	push   0x0
  533b65:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  533b6b:	8b ce                	mov    ecx,esi
  533b6d:	6a 00                	push   0x0
  533b6f:	50                   	push   eax
  533b70:	e8 2b aa fd ff       	call   0x50e5a0
  533b75:	8d 8d f8 fb ff ff    	lea    ecx,[ebp-0x408]
  533b7b:	83 c4 0c             	add    esp,0xc
  533b7e:	8d 51 01             	lea    edx,[ecx+0x1]
  533b81:	8a 01                	mov    al,BYTE PTR [ecx]
  533b83:	41                   	inc    ecx
  533b84:	84 c0                	test   al,al
  533b86:	75 f9                	jne    0x533b81
  533b88:	a1 a0 97 5e 00       	mov    eax,ds:0x5e97a0
  533b8d:	2b ca                	sub    ecx,edx
  533b8f:	8d 04 c8             	lea    eax,[eax+ecx*8]
  533b92:	83 c0 08             	add    eax,0x8
  533b95:	a3 a0 97 5e 00       	mov    ds:0x5e97a0,eax
  533b9a:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  533b9d:	5f                   	pop    edi
  533b9e:	5e                   	pop    esi
  533b9f:	33 cd                	xor    ecx,ebp
  533ba1:	5b                   	pop    ebx
  533ba2:	e8 07 65 05 00       	call   0x58a0ae
  533ba7:	8b e5                	mov    esp,ebp
  533ba9:	5d                   	pop    ebp
  533baa:	c3                   	ret
  533bab:	cc                   	int3
  533bac:	cc                   	int3
  533bad:	cc                   	int3
  533bae:	cc                   	int3
  533baf:	cc                   	int3
  534350:	55                   	push   ebp
  534351:	8b ec                	mov    ebp,esp
  534353:	81 ec d4 00 00 00    	sub    esp,0xd4
  534359:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  53435e:	33 c5                	xor    eax,ebp
  534360:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  534363:	53                   	push   ebx
  534364:	56                   	push   esi
  534365:	57                   	push   edi
  534366:	8b f9                	mov    edi,ecx
  534368:	c6 45 98 00          	mov    BYTE PTR [ebp-0x68],0x0
  53436c:	8b d7                	mov    edx,edi
  53436e:	89 bd 30 ff ff ff    	mov    DWORD PTR [ebp-0xd0],edi
  534374:	33 db                	xor    ebx,ebx
  534376:	8d 72 01             	lea    esi,[edx+0x1]
  534379:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [eax+0x0]
  534380:	8a 02                	mov    al,BYTE PTR [edx]
  534382:	42                   	inc    edx
  534383:	84 c0                	test   al,al
  534385:	75 f9                	jne    0x534380
  534387:	2b d6                	sub    edx,esi
  534389:	0f 84 f2 00 00 00    	je     0x534481
  53438f:	90                   	nop
  534390:	0f b6 04 1f          	movzx  eax,BYTE PTR [edi+ebx*1]
  534394:	50                   	push   eax
  534395:	8d 85 34 ff ff ff    	lea    eax,[ebp-0xcc]
  53439b:	68 dc d6 58 00       	push   0x58d6dc
  5343a0:	50                   	push   eax
  5343a1:	e8 2a cd ec ff       	call   0x4010d0
  5343a6:	8d 95 34 ff ff ff    	lea    edx,[ebp-0xcc]
  5343ac:	83 c4 0c             	add    esp,0xc
  5343af:	8b f2                	mov    esi,edx
  5343b1:	8a 02                	mov    al,BYTE PTR [edx]
  5343b3:	42                   	inc    edx
  5343b4:	84 c0                	test   al,al
  5343b6:	75 f9                	jne    0x5343b1
  5343b8:	8d 7d 98             	lea    edi,[ebp-0x68]
  5343bb:	2b d6                	sub    edx,esi
  5343bd:	4f                   	dec    edi
  5343be:	66 90                	xchg   ax,ax
  5343c0:	8a 47 01             	mov    al,BYTE PTR [edi+0x1]
  5343c3:	47                   	inc    edi
  5343c4:	84 c0                	test   al,al
  5343c6:	75 f8                	jne    0x5343c0
  5343c8:	8b ca                	mov    ecx,edx
  5343ca:	c1 e9 02             	shr    ecx,0x2
  5343cd:	f3 a5                	rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
  5343cf:	8b ca                	mov    ecx,edx
  5343d1:	83 e1 03             	and    ecx,0x3
  5343d4:	f3 a4                	rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
  5343d6:	8b bd 30 ff ff ff    	mov    edi,DWORD PTR [ebp-0xd0]
  5343dc:	0f b6 04 1f          	movzx  eax,BYTE PTR [edi+ebx*1]
  5343e0:	50                   	push   eax
  5343e1:	68 a8 16 5b 00       	push   0x5b16a8
  5343e6:	ff 15 48 c3 58 00    	call   DWORD PTR ds:0x58c348
  5343ec:	83 c4 08             	add    esp,0x8
  5343ef:	85 c0                	test   eax,eax
  5343f1:	74 77                	je     0x53446a
  5343f3:	8d 4d 98             	lea    ecx,[ebp-0x68]
  5343f6:	8d 51 01             	lea    edx,[ecx+0x1]
  5343f9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [eax+0x0]
  534400:	8a 01                	mov    al,BYTE PTR [ecx]
  534402:	41                   	inc    ecx
  534403:	84 c0                	test   al,al
  534405:	75 f9                	jne    0x534400
  534407:	8b 35 9c 97 5e 00    	mov    esi,DWORD PTR ds:0x5e979c
  53440d:	2b ca                	sub    ecx,edx
  53440f:	8b 15 a4 97 5e 00    	mov    edx,DWORD PTR ds:0x5e97a4
  534415:	8d 04 ce             	lea    eax,[esi+ecx*8]
  534418:	3d ca 01 00 00       	cmp    eax,0x1ca
  53441d:	76 14                	jbe    0x534433
  53441f:	be af 00 00 00       	mov    esi,0xaf
  534424:	83 c2 0a             	add    edx,0xa
  534427:	89 35 9c 97 5e 00    	mov    DWORD PTR ds:0x5e979c,esi
  53442d:	89 15 a4 97 5e 00    	mov    DWORD PTR ds:0x5e97a4,edx
  534433:	6a 00                	push   0x0
  534435:	8d 45 98             	lea    eax,[ebp-0x68]
  534438:	8b ce                	mov    ecx,esi
  53443a:	6a 00                	push   0x0
  53443c:	50                   	push   eax
  53443d:	e8 5e a1 fd ff       	call   0x50e5a0
  534442:	8d 4d 98             	lea    ecx,[ebp-0x68]
  534445:	83 c4 0c             	add    esp,0xc
  534448:	8d 51 01             	lea    edx,[ecx+0x1]
  53444b:	0f 1f 44 00 00       	nop    DWORD PTR [eax+eax*1+0x0]
  534450:	8a 01                	mov    al,BYTE PTR [ecx]
  534452:	41                   	inc    ecx
  534453:	84 c0                	test   al,al
  534455:	75 f9                	jne    0x534450
  534457:	a1 9c 97 5e 00       	mov    eax,ds:0x5e979c
  53445c:	2b ca                	sub    ecx,edx
  53445e:	c6 45 98 00          	mov    BYTE PTR [ebp-0x68],0x0
  534462:	8d 04 c8             	lea    eax,[eax+ecx*8]
  534465:	a3 9c 97 5e 00       	mov    ds:0x5e979c,eax
  53446a:	8b c7                	mov    eax,edi
  53446c:	43                   	inc    ebx
  53446d:	8d 50 01             	lea    edx,[eax+0x1]
  534470:	8a 08                	mov    cl,BYTE PTR [eax]
  534472:	40                   	inc    eax
  534473:	84 c9                	test   cl,cl
  534475:	75 f9                	jne    0x534470
  534477:	2b c2                	sub    eax,edx
  534479:	3b d8                	cmp    ebx,eax
  53447b:	0f 82 0f ff ff ff    	jb     0x534390
  534481:	8b 15 a4 97 5e 00    	mov    edx,DWORD PTR ds:0x5e97a4
  534487:	8d 45 98             	lea    eax,[ebp-0x68]
  53448a:	8b 0d 9c 97 5e 00    	mov    ecx,DWORD PTR ds:0x5e979c
  534490:	6a 00                	push   0x0
  534492:	6a 00                	push   0x0
  534494:	50                   	push   eax
  534495:	e8 06 a1 fd ff       	call   0x50e5a0
  53449a:	83 c4 0c             	add    esp,0xc
  53449d:	8d 4d 98             	lea    ecx,[ebp-0x68]
  5344a0:	8d 51 01             	lea    edx,[ecx+0x1]
  5344a3:	5f                   	pop    edi
  5344a4:	5e                   	pop    esi
  5344a5:	5b                   	pop    ebx
  5344a6:	8a 01                	mov    al,BYTE PTR [ecx]
  5344a8:	41                   	inc    ecx
  5344a9:	84 c0                	test   al,al
  5344ab:	75 f9                	jne    0x5344a6
  5344ad:	a1 9c 97 5e 00       	mov    eax,ds:0x5e979c
  5344b2:	2b ca                	sub    ecx,edx
  5344b4:	8d 04 c8             	lea    eax,[eax+ecx*8]
  5344b7:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  5344ba:	83 c0 08             	add    eax,0x8
  5344bd:	33 cd                	xor    ecx,ebp
  5344bf:	a3 9c 97 5e 00       	mov    ds:0x5e979c,eax
  5344c4:	e8 e5 5b 05 00       	call   0x58a0ae
  5344c9:	8b e5                	mov    esp,ebp
  5344cb:	5d                   	pop    ebp
  5344cc:	c3                   	ret
  5344cd:	cc                   	int3
  5344ce:	cc                   	int3
  5344cf:	cc                   	int3
  534790:	55                   	push   ebp
  534791:	8b ec                	mov    ebp,esp
  534793:	81 ec 1c 04 00 00    	sub    esp,0x41c
  534799:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  53479e:	33 c5                	xor    eax,ebp
  5347a0:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  5347a3:	83 3d 34 06 62 0a 02 	cmp    DWORD PTR ds:0xa620634,0x2
  5347aa:	b8 e8 03 00 00       	mov    eax,0x3e8
  5347af:	53                   	push   ebx
  5347b0:	8b 1d f8 c1 58 00    	mov    ebx,DWORD PTR ds:0x58c1f8
  5347b6:	56                   	push   esi
  5347b7:	57                   	push   edi
  5347b8:	75 16                	jne    0x5347d0
  5347ba:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  5347bf:	6a 00                	push   0x0
  5347c1:	68 a8 00 00 00       	push   0xa8
  5347c6:	6a 00                	push   0x0
  5347c8:	ff 70 04             	push   DWORD PTR [eax+0x4]
  5347cb:	ff d3                	call   ebx
  5347cd:	83 c4 10             	add    esp,0x10
  5347d0:	50                   	push   eax
  5347d1:	68 36 01 00 00       	push   0x136
  5347d6:	68 0c 03 00 00       	push   0x30c
  5347db:	ba 28 00 00 00       	mov    edx,0x28
  5347e0:	b9 03 02 00 00       	mov    ecx,0x203
  5347e5:	e8 b6 cb fd ff       	call   0x5113a0
  5347ea:	a1 b8 3a 61 0a       	mov    eax,ds:0xa613ab8
  5347ef:	83 c4 0c             	add    esp,0xc
  5347f2:	83 f8 02             	cmp    eax,0x2
  5347f5:	74 13                	je     0x53480a
  5347f7:	83 f8 03             	cmp    eax,0x3
  5347fa:	74 0e                	je     0x53480a
  5347fc:	83 f8 0a             	cmp    eax,0xa
  5347ff:	74 09                	je     0x53480a
  534801:	83 f8 0b             	cmp    eax,0xb
  534804:	0f 85 ab 02 00 00    	jne    0x534ab5
  53480a:	83 3d 34 06 62 0a 00 	cmp    DWORD PTR ds:0xa620634,0x0
  534811:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  534816:	6a 01                	push   0x1
  534818:	6a 54                	push   0x54
  53481a:	68 fc 00 00 00       	push   0xfc
  53481f:	68 fc 00 00 00       	push   0xfc
  534824:	ff 70 04             	push   DWORD PTR [eax+0x4]
  534827:	0f 85 92 00 00 00    	jne    0x5348bf
  53482d:	ff d3                	call   ebx
  53482f:	83 c4 10             	add    esp,0x10
  534832:	ba 37 00 00 00       	mov    edx,0x37
  534837:	b9 0d 02 00 00       	mov    ecx,0x20d
  53483c:	50                   	push   eax
  53483d:	68 40 1a 5b 00       	push   0x5b1a40
  534842:	e8 59 9d fd ff       	call   0x50e5a0
  534847:	a1 b8 3a 61 0a       	mov    eax,ds:0xa613ab8
  53484c:	83 c4 0c             	add    esp,0xc
  53484f:	6a 01                	push   0x1
  534851:	6a 54                	push   0x54
  534853:	68 fc 00 00 00       	push   0xfc
  534858:	68 fc 00 00 00       	push   0xfc
  53485d:	83 f8 03             	cmp    eax,0x3
  534860:	75 15                	jne    0x534877
  534862:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  534867:	ff 70 04             	push   DWORD PTR [eax+0x4]
  53486a:	ff d3                	call   ebx
  53486c:	83 c4 10             	add    esp,0x10
  53486f:	50                   	push   eax
  534870:	68 5c 1a 5b 00       	push   0x5b1a5c
  534875:	eb 25                	jmp    0x53489c
  534877:	83 f8 0b             	cmp    eax,0xb
  53487a:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  53487f:	ff 70 04             	push   DWORD PTR [eax+0x4]
  534882:	75 0d                	jne    0x534891
  534884:	ff d3                	call   ebx
  534886:	83 c4 10             	add    esp,0x10
  534889:	50                   	push   eax
  53488a:	68 68 1a 5b 00       	push   0x5b1a68
  53488f:	eb 0b                	jmp    0x53489c
  534891:	ff d3                	call   ebx
  534893:	83 c4 10             	add    esp,0x10
  534896:	50                   	push   eax
  534897:	68 80 1a 5b 00       	push   0x5b1a80
  53489c:	ba 41 00 00 00       	mov    edx,0x41
  5348a1:	b9 0d 02 00 00       	mov    ecx,0x20d
  5348a6:	e8 f5 9c fd ff       	call   0x50e5a0
  5348ab:	83 c4 0c             	add    esp,0xc
  5348ae:	5f                   	pop    edi
  5348af:	5e                   	pop    esi
  5348b0:	5b                   	pop    ebx
  5348b1:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  5348b4:	33 cd                	xor    ecx,ebp
  5348b6:	e8 f3 57 05 00       	call   0x58a0ae
  5348bb:	8b e5                	mov    esp,ebp
  5348bd:	5d                   	pop    ebp
  5348be:	c3                   	ret
  5348bf:	ff d3                	call   ebx
  5348c1:	83 c4 10             	add    esp,0x10
  5348c4:	ba 37 00 00 00       	mov    edx,0x37
  5348c9:	b9 0d 02 00 00       	mov    ecx,0x20d
  5348ce:	50                   	push   eax
  5348cf:	68 40 1a 5b 00       	push   0x5b1a40
  5348d4:	e8 c7 9c fd ff       	call   0x50e5a0
  5348d9:	83 c4 08             	add    esp,0x8
  5348dc:	ba 41 00 00 00       	mov    edx,0x41
  5348e1:	b9 0d 02 00 00       	mov    ecx,0x20d
  5348e6:	6a 0f                	push   0xf
  5348e8:	68 f5 00 00 00       	push   0xf5
  5348ed:	e8 8e cb fd ff       	call   0x511480
  5348f2:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  5348f7:	83 c4 0c             	add    esp,0xc
  5348fa:	6a 01                	push   0x1
  5348fc:	68 ff 00 00 00       	push   0xff
  534901:	68 ff 00 00 00       	push   0xff
  534906:	68 ff 00 00 00       	push   0xff
  53490b:	ff 70 04             	push   DWORD PTR [eax+0x4]
  53490e:	ff d3                	call   ebx
  534910:	83 c4 10             	add    esp,0x10
  534913:	ba 44 00 00 00       	mov    edx,0x44
  534918:	b9 17 02 00 00       	mov    ecx,0x217
  53491d:	50                   	push   eax
  53491e:	68 e0 05 62 0a       	push   0xa6205e0
  534923:	e8 78 9c fd ff       	call   0x50e5a0
  534928:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  53492d:	83 c4 0c             	add    esp,0xc
  534930:	6a 01                	push   0x1
  534932:	6a 54                	push   0x54
  534934:	68 fc 00 00 00       	push   0xfc
  534939:	68 fc 00 00 00       	push   0xfc
  53493e:	ff 70 04             	push   DWORD PTR [eax+0x4]
  534941:	ff d3                	call   ebx
  534943:	83 c4 10             	add    esp,0x10
  534946:	ba 50 00 00 00       	mov    edx,0x50
  53494b:	b9 0d 02 00 00       	mov    ecx,0x20d
  534950:	50                   	push   eax
  534951:	68 8c 1a 5b 00       	push   0x5b1a8c
  534956:	e8 45 9c fd ff       	call   0x50e5a0
  53495b:	83 c4 08             	add    esp,0x8
  53495e:	c7 85 e4 fb ff ff 5f 	mov    DWORD PTR [ebp-0x41c],0x5f
  534965:	00 00 00 
  534968:	ba 5a 00 00 00       	mov    edx,0x5a
  53496d:	b9 0d 02 00 00       	mov    ecx,0x20d
  534972:	68 c8 00 00 00       	push   0xc8
  534977:	68 f5 00 00 00       	push   0xf5
  53497c:	e8 ff ca fd ff       	call   0x511480
  534981:	83 c4 0c             	add    esp,0xc
  534984:	83 3d 40 06 62 0a 00 	cmp    DWORD PTR ds:0xa620640,0x0
  53498b:	75 3b                	jne    0x5349c8
  53498d:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  534992:	6a 01                	push   0x1
  534994:	68 ab 00 00 00       	push   0xab
  534999:	68 ab 00 00 00       	push   0xab
  53499e:	68 ab 00 00 00       	push   0xab
  5349a3:	ff 70 04             	push   DWORD PTR [eax+0x4]
  5349a6:	ff d3                	call   ebx
  5349a8:	83 c4 10             	add    esp,0x10
  5349ab:	ba 5f 00 00 00       	mov    edx,0x5f
  5349b0:	b9 17 02 00 00       	mov    ecx,0x217
  5349b5:	50                   	push   eax
  5349b6:	68 ac 1a 5b 00       	push   0x5b1aac
  5349bb:	e8 e0 9b fd ff       	call   0x50e5a0
  5349c0:	83 c4 0c             	add    esp,0xc
  5349c3:	e9 ba 00 00 00       	jmp    0x534a82
  5349c8:	33 f6                	xor    esi,esi
  5349ca:	66 0f 1f 44 00 00    	nop    WORD PTR [eax+eax*1+0x0]
  5349d0:	8b be 40 06 62 0a    	mov    edi,DWORD PTR [esi+0xa620640]
  5349d6:	85 ff                	test   edi,edi
  5349d8:	0f 84 98 00 00 00    	je     0x534a76
  5349de:	8b cf                	mov    ecx,edi
  5349e0:	e8 2b b7 f8 ff       	call   0x4c0110
  5349e5:	8b 96 90 05 62 0a    	mov    edx,DWORD PTR [esi+0xa620590]
  5349eb:	8b cf                	mov    ecx,edi
  5349ed:	6a 01                	push   0x1
  5349ef:	e8 4c dc f1 ff       	call   0x452640
  5349f4:	83 c4 04             	add    esp,0x4
  5349f7:	50                   	push   eax
  5349f8:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  5349fe:	68 70 c6 58 00       	push   0x58c670
  534a03:	50                   	push   eax
  534a04:	e8 c7 c6 ec ff       	call   0x4010d0
  534a09:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  534a0f:	83 c4 0c             	add    esp,0xc
  534a12:	8d 50 01             	lea    edx,[eax+0x1]
  534a15:	8a 08                	mov    cl,BYTE PTR [eax]
  534a17:	40                   	inc    eax
  534a18:	84 c9                	test   cl,cl
  534a1a:	75 f9                	jne    0x534a15
  534a1c:	2b c2                	sub    eax,edx
  534a1e:	83 f8 1c             	cmp    eax,0x1c
  534a21:	72 0f                	jb     0x534a32
  534a23:	66 c7 85 12 fc ff ff 	mov    WORD PTR [ebp-0x3ee],0x2e2e
  534a2a:	2e 2e 
  534a2c:	88 8d 14 fc ff ff    	mov    BYTE PTR [ebp-0x3ec],cl
  534a32:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  534a37:	6a 01                	push   0x1
  534a39:	68 ff 00 00 00       	push   0xff
  534a3e:	68 ff 00 00 00       	push   0xff
  534a43:	68 ff 00 00 00       	push   0xff
  534a48:	ff 70 04             	push   DWORD PTR [eax+0x4]
  534a4b:	ff d3                	call   ebx
  534a4d:	8b bd e4 fb ff ff    	mov    edi,DWORD PTR [ebp-0x41c]
  534a53:	83 c4 10             	add    esp,0x10
  534a56:	8b d7                	mov    edx,edi
  534a58:	b9 17 02 00 00       	mov    ecx,0x217
  534a5d:	50                   	push   eax
  534a5e:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  534a64:	50                   	push   eax
  534a65:	e8 36 9b fd ff       	call   0x50e5a0
  534a6a:	83 c4 0c             	add    esp,0xc
  534a6d:	83 c7 0a             	add    edi,0xa
  534a70:	89 bd e4 fb ff ff    	mov    DWORD PTR [ebp-0x41c],edi
  534a76:	83 c6 04             	add    esi,0x4
  534a79:	83 fe 50             	cmp    esi,0x50
  534a7c:	0f 8c 4e ff ff ff    	jl     0x5349d0
  534a82:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  534a87:	6a 01                	push   0x1
  534a89:	6a 54                	push   0x54
  534a8b:	68 fc 00 00 00       	push   0xfc
  534a90:	68 fc 00 00 00       	push   0xfc
  534a95:	ff 70 04             	push   DWORD PTR [eax+0x4]
  534a98:	ff d3                	call   ebx
  534a9a:	83 c4 10             	add    esp,0x10
  534a9d:	ba 27 01 00 00       	mov    edx,0x127
  534aa2:	b9 0d 02 00 00       	mov    ecx,0x20d
  534aa7:	50                   	push   eax
  534aa8:	68 c4 1a 5b 00       	push   0x5b1ac4
  534aad:	e8 ee 9a fd ff       	call   0x50e5a0
  534ab2:	83 c4 0c             	add    esp,0xc
  534ab5:	83 3d 34 06 62 0a 02 	cmp    DWORD PTR ds:0xa620634,0x2
  534abc:	0f 85 87 00 00 00    	jne    0x534b49
  534ac2:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  534ac7:	6a 00                	push   0x0
  534ac9:	68 a8 00 00 00       	push   0xa8
  534ace:	6a 00                	push   0x0
  534ad0:	ff 70 04             	push   DWORD PTR [eax+0x4]
  534ad3:	ff d3                	call   ebx
  534ad5:	50                   	push   eax
  534ad6:	6a 00                	push   0x0
  534ad8:	ff 35 20 bd 5b 0a    	push   DWORD PTR ds:0xa5bbd20
  534ade:	ff 15 e8 c1 58 00    	call   DWORD PTR ds:0x58c1e8
  534ae4:	0f 28 05 40 da 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5dda40
  534aeb:	83 c4 1c             	add    esp,0x1c
  534aee:	8b 3d 00 c2 58 00    	mov    edi,DWORD PTR ds:0x58c200
  534af4:	0f 11 85 e8 fb ff ff 	movups XMMWORD PTR [ebp-0x418],xmm0
  534afb:	6a 01                	push   0x1
  534afd:	ff 35 20 bd 5b 0a    	push   DWORD PTR ds:0xa5bbd20
  534b03:	ff d7                	call   edi
  534b05:	8b 35 0c c2 58 00    	mov    esi,DWORD PTR ds:0x58c20c
  534b0b:	6a 50                	push   0x50
  534b0d:	ff 35 20 bd 5b 0a    	push   DWORD PTR ds:0xa5bbd20
  534b13:	ff d6                	call   esi
  534b15:	8d 85 e8 fb ff ff    	lea    eax,[ebp-0x418]
  534b1b:	50                   	push   eax
  534b1c:	ff 35 10 bb 5b 06    	push   DWORD PTR ds:0x65bbb10
  534b22:	50                   	push   eax
  534b23:	ff 35 20 bd 5b 0a    	push   DWORD PTR ds:0xa5bbd20
  534b29:	ff 15 04 c2 58 00    	call   DWORD PTR ds:0x58c204
  534b2f:	6a 00                	push   0x0
  534b31:	ff 35 20 bd 5b 0a    	push   DWORD PTR ds:0xa5bbd20
  534b37:	ff d7                	call   edi
  534b39:	68 ff 00 00 00       	push   0xff
  534b3e:	ff 35 20 bd 5b 0a    	push   DWORD PTR ds:0xa5bbd20
  534b44:	ff d6                	call   esi
  534b46:	83 c4 30             	add    esp,0x30
  534b49:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  534b4c:	5f                   	pop    edi
  534b4d:	5e                   	pop    esi
  534b4e:	33 cd                	xor    ecx,ebp
  534b50:	5b                   	pop    ebx
  534b51:	e8 58 55 05 00       	call   0x58a0ae
  534b56:	8b e5                	mov    esp,ebp
  534b58:	5d                   	pop    ebp
  534b59:	c3                   	ret
  534b5a:	cc                   	int3
  534b5b:	cc                   	int3
  534b5c:	cc                   	int3
  534b5d:	cc                   	int3
  534b5e:	cc                   	int3
  534b5f:	cc                   	int3
  534d90:	55                   	push   ebp
  534d91:	8b ec                	mov    ebp,esp
  534d93:	81 ec 18 04 00 00    	sub    esp,0x418
  534d99:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  534d9e:	33 c5                	xor    eax,ebp
  534da0:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  534da3:	0f 28 05 b0 d9 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5dd9b0
  534daa:	56                   	push   esi
  534dab:	57                   	push   edi
  534dac:	8b f2                	mov    esi,edx
  534dae:	8b f9                	mov    edi,ecx
  534db0:	8d 95 e8 fb ff ff    	lea    edx,[ebp-0x418]
  534db6:	b9 d8 1a 5b 00       	mov    ecx,0x5b1ad8
  534dbb:	0f 11 85 e8 fb ff ff 	movups XMMWORD PTR [ebp-0x418],xmm0
  534dc2:	e8 79 77 fd ff       	call   0x50c540
  534dc7:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  534dcc:	6a 78                	push   0x78
  534dce:	6a 58                	push   0x58
  534dd0:	6a 38                	push   0x38
  534dd2:	ff 70 04             	push   DWORD PTR [eax+0x4]
  534dd5:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  534ddb:	50                   	push   eax
  534ddc:	68 00 10 00 00       	push   0x1000
  534de1:	68 16 c6 58 00       	push   0x58c616
  534de6:	6a 78                	push   0x78
  534de8:	68 b8 01 00 00       	push   0x1b8
  534ded:	ba b8 01 00 00       	mov    edx,0x1b8
  534df2:	b9 0f 00 00 00       	mov    ecx,0xf
  534df7:	e8 74 14 fe ff       	call   0x516270
  534dfc:	83 c4 24             	add    esp,0x24
  534dff:	85 ff                	test   edi,edi
  534e01:	74 27                	je     0x534e2a
  534e03:	69 05 30 06 62 0a 68 	imul   eax,DWORD PTR ds:0xa620630,0x568
  534e0a:	05 00 00 
  534e0d:	56                   	push   esi
  534e0e:	05 08 14 15 06       	add    eax,0x6151408
  534e13:	50                   	push   eax
  534e14:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  534e1a:	68 80 c6 58 00       	push   0x58c680
  534e1f:	50                   	push   eax
  534e20:	e8 ab c2 ec ff       	call   0x4010d0
  534e25:	83 c4 10             	add    esp,0x10
  534e28:	eb 15                	jmp    0x534e3f
  534e2a:	8d 8d f8 fb ff ff    	lea    ecx,[ebp-0x408]
  534e30:	2b ce                	sub    ecx,esi
  534e32:	8a 06                	mov    al,BYTE PTR [esi]
  534e34:	8d 76 01             	lea    esi,[esi+0x1]
  534e37:	88 44 31 ff          	mov    BYTE PTR [ecx+esi*1-0x1],al
  534e3b:	84 c0                	test   al,al
  534e3d:	75 f3                	jne    0x534e32
  534e3f:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  534e44:	6a 01                	push   0x1
  534e46:	6a 54                	push   0x54
  534e48:	68 fc 00 00 00       	push   0xfc
  534e4d:	68 fc 00 00 00       	push   0xfc
  534e52:	ff 70 04             	push   DWORD PTR [eax+0x4]
  534e55:	ff 15 f8 c1 58 00    	call   DWORD PTR ds:0x58c1f8
  534e5b:	83 c4 10             	add    esp,0x10
  534e5e:	ba c2 01 00 00       	mov    edx,0x1c2
  534e63:	b9 19 00 00 00       	mov    ecx,0x19
  534e68:	50                   	push   eax
  534e69:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  534e6f:	50                   	push   eax
  534e70:	68 a4 01 00 00       	push   0x1a4
  534e75:	e8 96 9a fd ff       	call   0x50e910
  534e7a:	68 e4 1a 5b 00       	push   0x5b1ae4
  534e7f:	ba 12 02 00 00       	mov    edx,0x212
  534e84:	b9 41 00 00 00       	mov    ecx,0x41
  534e89:	e8 f2 f7 fd ff       	call   0x514680
  534e8e:	83 c4 14             	add    esp,0x14
  534e91:	e8 ea ed f9 ff       	call   0x4d3c80
  534e96:	b9 d8 1a 5b 00       	mov    ecx,0x5b1ad8
  534e9b:	e8 f0 77 fd ff       	call   0x50c690
  534ea0:	b9 d8 1a 5b 00       	mov    ecx,0x5b1ad8
  534ea5:	e8 16 76 fd ff       	call   0x50c4c0
  534eaa:	8b 4d fc             	mov    ecx,DWORD PTR [ebp-0x4]
  534ead:	5f                   	pop    edi
  534eae:	33 cd                	xor    ecx,ebp
  534eb0:	5e                   	pop    esi
  534eb1:	e8 f8 51 05 00       	call   0x58a0ae
  534eb6:	8b e5                	mov    esp,ebp
  534eb8:	5d                   	pop    ebp
  534eb9:	c3                   	ret
  534eba:	cc                   	int3
  534ebb:	cc                   	int3
  534ebc:	cc                   	int3
  534ebd:	cc                   	int3
  534ebe:	cc                   	int3
  534ebf:	cc                   	int3
  542665:	0f 28 05 20 da 5d 00 	movaps xmm0,XMMWORD PTR ds:0x5dda20
  54266c:	8d 95 80 f7 ff ff    	lea    edx,[ebp-0x880]
  542672:	b9 fc 61 5b 00       	mov    ecx,0x5b61fc
  542677:	0f 11 85 80 f7 ff ff 	movups XMMWORD PTR [ebp-0x880],xmm0
  54267e:	e8 bd 9e fc ff       	call   0x50c540
  542683:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  542688:	8b 1d f8 c1 58 00    	mov    ebx,DWORD PTR ds:0x58c1f8
  54268e:	68 8c 00 00 00       	push   0x8c
  542693:	68 e6 00 00 00       	push   0xe6
  542698:	68 f0 00 00 00       	push   0xf0
  54269d:	ff 70 04             	push   DWORD PTR [eax+0x4]
  5426a0:	ff d3                	call   ebx
  5426a2:	6a 00                	push   0x0
  5426a4:	ff b5 8c f7 ff ff    	push   DWORD PTR [ebp-0x874]
  5426aa:	ba 04 62 5b 00       	mov    edx,0x5b6204
  5426af:	8b c8                	mov    ecx,eax
  5426b1:	ff b5 88 f7 ff ff    	push   DWORD PTR [ebp-0x878]
  5426b7:	ff b5 84 f7 ff ff    	push   DWORD PTR [ebp-0x87c]
  5426bd:	ff b5 80 f7 ff ff    	push   DWORD PTR [ebp-0x880]
  5426c3:	e8 c8 d0 f8 ff       	call   0x4cf790
  5426c8:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  5426cd:	83 c4 24             	add    esp,0x24
  5426d0:	6a 54                	push   0x54
  5426d2:	68 fc 00 00 00       	push   0xfc
  5426d7:	68 fc 00 00 00       	push   0xfc
  5426dc:	ff 70 04             	push   DWORD PTR [eax+0x4]
  5426df:	ff d3                	call   ebx
  5426e1:	8b 0d 8c 4b 35 06    	mov    ecx,DWORD PTR ds:0x6354b8c
  5426e7:	83 c4 10             	add    esp,0x10
  5426ea:	85 c0                	test   eax,eax
  5426ec:	c7 05 a8 4a 35 06 00 	mov    DWORD PTR ds:0x6354aa8,0x0
  5426f3:	00 00 00 
  5426f6:	0f 49 c8             	cmovns ecx,eax
  5426f9:	83 f8 fe             	cmp    eax,0xfffffffe
  5426fc:	89 0d 8c 4b 35 06    	mov    DWORD PTR ds:0x6354b8c,ecx
  542702:	b8 01 00 00 00       	mov    eax,0x1
  542707:	8b 0d 9c 4a 35 06    	mov    ecx,DWORD PTR ds:0x6354a9c
  54270d:	0f 44 c8             	cmove  ecx,eax
  542710:	89 0d 9c 4a 35 06    	mov    DWORD PTR ds:0x6354a9c,ecx
  542716:	33 c9                	xor    ecx,ecx
  542718:	0f 1f 84 00 00 00 00 	nop    DWORD PTR [eax+eax*1+0x0]
  54271f:	00 
  542720:	8a 81 16 c6 58 00    	mov    al,BYTE PTR [ecx+0x58c616]
  542726:	8d 49 01             	lea    ecx,[ecx+0x1]
  542729:	88 81 c3 4a 35 06    	mov    BYTE PTR [ecx+0x6354ac3],al
  54272f:	84 c0                	test   al,al
  542731:	75 ed                	jne    0x542720
  542733:	33 c9                	xor    ecx,ecx
  542735:	66 66 66 0f 1f 84 00 	data16 data16 nop WORD PTR [eax+eax*1+0x0]
  54273c:	00 00 00 00 
  542740:	8a 81 16 c6 58 00    	mov    al,BYTE PTR [ecx+0x58c616]
  542746:	8d 49 01             	lea    ecx,[ecx+0x1]
  542749:	88 81 27 4b 35 06    	mov    BYTE PTR [ecx+0x6354b27],al
  54274f:	84 c0                	test   al,al
  542751:	75 ed                	jne    0x542740
  542753:	c7 05 b4 4a 35 06 01 	mov    DWORD PTR ds:0x6354ab4,0x1
  54275a:	00 00 00 
  54275d:	be 9c 28 61 0a       	mov    esi,0xa61289c
  542762:	c6 05 ac 4a 35 06 01 	mov    BYTE PTR ds:0x6354aac,0x1
  542769:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [eax+0x0]
  542770:	8d 4e 64             	lea    ecx,[esi+0x64]
  542773:	8d 51 01             	lea    edx,[ecx+0x1]
  542776:	8a 01                	mov    al,BYTE PTR [ecx]
  542778:	41                   	inc    ecx
  542779:	84 c0                	test   al,al
  54277b:	75 f9                	jne    0x542776
  54277d:	2b ca                	sub    ecx,edx
  54277f:	74 0a                	je     0x54278b
  542781:	8b 4e fc             	mov    ecx,DWORD PTR [esi-0x4]
  542784:	8b d6                	mov    edx,esi
  542786:	e8 05 d2 f8 ff       	call   0x4cf990
  54278b:	81 c6 9c 01 00 00    	add    esi,0x19c
  542791:	81 fe b4 38 61 0a    	cmp    esi,0xa6138b4
  542797:	7c d7                	jl     0x542770
  542799:	b9 9c 28 61 0a       	mov    ecx,0xa61289c
  54279e:	8d 51 01             	lea    edx,[ecx+0x1]
  5427a1:	8a 01                	mov    al,BYTE PTR [ecx]
  5427a3:	41                   	inc    ecx
  5427a4:	84 c0                	test   al,al
  5427a6:	75 f9                	jne    0x5427a1
  5427a8:	2b ca                	sub    ecx,edx
  5427aa:	74 0c                	je     0x5427b8
  5427ac:	ba 16 c6 58 00       	mov    edx,0x58c616
  5427b1:	33 c9                	xor    ecx,ecx
  5427b3:	e8 d8 d1 f8 ff       	call   0x4cf990
  5427b8:	80 3d cb 7e 38 03 00 	cmp    BYTE PTR ds:0x3387ecb,0x0
  5427bf:	75 2f                	jne    0x5427f0
  5427c1:	ba 20 62 5b 00       	mov    edx,0x5b6220
  5427c6:	b9 1b 00 00 00       	mov    ecx,0x1b
  5427cb:	e8 c0 d1 f8 ff       	call   0x4cf990
  5427d0:	ba 16 c6 58 00       	mov    edx,0x58c616
  5427d5:	33 c9                	xor    ecx,ecx
  5427d7:	e8 b4 d1 f8 ff       	call   0x4cf990
  5427dc:	ba 30 62 5b 00       	mov    edx,0x5b6230
  5427e1:	b9 30 00 00 00       	mov    ecx,0x30
  5427e6:	e8 a5 d1 f8 ff       	call   0x4cf990
  5427eb:	0f 1f 44 00 00       	nop    DWORD PTR [eax+eax*1+0x0]
  5427f0:	e8 bb d7 f8 ff       	call   0x4cffb0
  5427f5:	e8 26 e9 f8 ff       	call   0x4d1120
  5427fa:	8b f8                	mov    edi,eax
  5427fc:	83 ff 64             	cmp    edi,0x64
  5427ff:	7d ef                	jge    0x5427f0
  542801:	85 ff                	test   edi,edi
  542803:	78 eb                	js     0x5427f0
  542805:	69 cf e8 00 00 00    	imul   ecx,edi,0xe8
  54280b:	8b 99 d8 ef 34 06    	mov    ebx,DWORD PTR [ecx+0x634efd8]
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
  55e9f0:	55                   	push   ebp
  55e9f1:	8b ec                	mov    ebp,esp
  55e9f3:	83 ec 0c             	sub    esp,0xc
  55e9f6:	56                   	push   esi
  55e9f7:	8b f1                	mov    esi,ecx
  55e9f9:	b8 67 66 66 66       	mov    eax,0x66666667
  55e9fe:	83 ec 08             	sub    esp,0x8
  55ea01:	8d 56 05             	lea    edx,[esi+0x5]
  55ea04:	f7 ea                	imul   edx
  55ea06:	c1 fa 02             	sar    edx,0x2
  55ea09:	8b c2                	mov    eax,edx
  55ea0b:	c1 e8 1f             	shr    eax,0x1f
  55ea0e:	03 c2                	add    eax,edx
  55ea10:	66 0f 6e c0          	movd   xmm0,eax
  55ea14:	f3 0f e6 c0          	cvtdq2pd xmm0,xmm0
  55ea18:	f2 0f 11 45 f8       	movsd  QWORD PTR [ebp-0x8],xmm0
  55ea1d:	dd 45 f8             	fld    QWORD PTR [ebp-0x8]
  55ea20:	dd 1c 24             	fstp   QWORD PTR [esp]
  55ea23:	e8 b4 cb 02 00       	call   0x58b5dc
  55ea28:	dd 5d f8             	fstp   QWORD PTR [ebp-0x8]
  55ea2b:	f2 0f 2c 45 f8       	cvttsd2si eax,QWORD PTR [ebp-0x8]
  55ea30:	83 c4 08             	add    esp,0x8
  55ea33:	85 f6                	test   esi,esi
  55ea35:	75 0f                	jne    0x55ea46
  55ea37:	33 c0                	xor    eax,eax
  55ea39:	6b c0 64             	imul   eax,eax,0x64
  55ea3c:	05 50 9f 5e 00       	add    eax,0x5e9f50
  55ea41:	5e                   	pop    esi
  55ea42:	8b e5                	mov    esp,ebp
  55ea44:	5d                   	pop    ebp
  55ea45:	c3                   	ret
  55ea46:	b9 0a 00 00 00       	mov    ecx,0xa
  55ea4b:	3b c1                	cmp    eax,ecx
  55ea4d:	5e                   	pop    esi
  55ea4e:	0f 4f c1             	cmovg  eax,ecx
  55ea51:	6b c0 64             	imul   eax,eax,0x64
  55ea54:	05 50 9f 5e 00       	add    eax,0x5e9f50
  55ea59:	8b e5                	mov    esp,ebp
  55ea5b:	5d                   	pop    ebp
  55ea5c:	c3                   	ret
  55ea5d:	cc                   	int3
  55ea5e:	cc                   	int3
  55ea5f:	cc                   	int3
  55ea60:	55                   	push   ebp
  55ea61:	8b ec                	mov    ebp,esp
  55ea63:	a1 a8 b7 84 0a       	mov    eax,ds:0xa84b7a8
  55ea68:	83 ec 08             	sub    esp,0x8
  55ea6b:	40                   	inc    eax
  55ea6c:	56                   	push   esi
  55ea6d:	57                   	push   edi
  55ea6e:	8b f9                	mov    edi,ecx
  55ea70:	25 ff 03 00 80       	and    eax,0x800003ff
  55ea75:	79 07                	jns    0x55ea7e
  55ea77:	48                   	dec    eax
  55ea78:	0d 00 fc ff ff       	or     eax,0xfffffc00
  55ea7d:	40                   	inc    eax
  55ea7e:	a3 a8 b7 84 0a       	mov    ds:0xa84b7a8,eax
  55ea83:	c1 e0 0a             	shl    eax,0xa
  55ea86:	68 00 04 00 00       	push   0x400
  55ea8b:	6a 00                	push   0x0
  55ea8d:	8d b0 b0 1e 94 0a    	lea    esi,[eax+0xa941eb0]
  55ea93:	56                   	push   esi
  55ea94:	e8 c7 c3 02 00       	call   0x58ae60
  55ea99:	8d 4f 05             	lea    ecx,[edi+0x5]
  55ea9c:	b8 67 66 66 66       	mov    eax,0x66666667
  55eaa1:	f7 e9                	imul   ecx
  55eaa3:	83 c4 04             	add    esp,0x4
  55eaa6:	c1 fa 02             	sar    edx,0x2
  55eaa9:	8b c2                	mov    eax,edx
  55eaab:	c1 e8 1f             	shr    eax,0x1f
  55eaae:	03 c2                	add    eax,edx
  55eab0:	66 0f 6e c0          	movd   xmm0,eax
  55eab4:	f3 0f e6 c0          	cvtdq2pd xmm0,xmm0
  55eab8:	f2 0f 11 45 f8       	movsd  QWORD PTR [ebp-0x8],xmm0
  55eabd:	dd 45 f8             	fld    QWORD PTR [ebp-0x8]
  55eac0:	dd 1c 24             	fstp   QWORD PTR [esp]
  55eac3:	e8 14 cb 02 00       	call   0x58b5dc
  55eac8:	dd 5d f8             	fstp   QWORD PTR [ebp-0x8]
  55eacb:	f2 0f 2c 45 f8       	cvttsd2si eax,QWORD PTR [ebp-0x8]
  55ead0:	83 c4 08             	add    esp,0x8
  55ead3:	85 ff                	test   edi,edi
  55ead5:	75 04                	jne    0x55eadb
  55ead7:	33 c0                	xor    eax,eax
  55ead9:	eb 0a                	jmp    0x55eae5
  55eadb:	b9 0a 00 00 00       	mov    ecx,0xa
  55eae0:	3b c1                	cmp    eax,ecx
  55eae2:	0f 4f c1             	cmovg  eax,ecx
  55eae5:	6b c0 64             	imul   eax,eax,0x64
  55eae8:	8b d6                	mov    edx,esi
  55eaea:	8d 88 50 9f 5e 00    	lea    ecx,[eax+0x5e9f50]
  55eaf0:	2b d1                	sub    edx,ecx
  55eaf2:	8a 01                	mov    al,BYTE PTR [ecx]
  55eaf4:	8d 49 01             	lea    ecx,[ecx+0x1]
  55eaf7:	88 44 0a ff          	mov    BYTE PTR [edx+ecx*1-0x1],al
  55eafb:	84 c0                	test   al,al
  55eafd:	75 f3                	jne    0x55eaf2
  55eaff:	68 c8 79 5d 00       	push   0x5d79c8
  55eb04:	56                   	push   esi
  55eb05:	ff 15 50 c3 58 00    	call   DWORD PTR ds:0x58c350
  55eb0b:	83 c4 08             	add    esp,0x8
  55eb0e:	85 c0                	test   eax,eax
  55eb10:	8b c6                	mov    eax,esi
  55eb12:	74 2e                	je     0x55eb42
  55eb14:	83 ff 55             	cmp    edi,0x55
  55eb17:	7d 29                	jge    0x55eb42
  55eb19:	f3 0f 7e 05 d0 79 5d 	movq   xmm0,QWORD PTR ds:0x5d79d0
  55eb20:	00 
  55eb21:	8b 0d d8 79 5d 00    	mov    ecx,DWORD PTR ds:0x5d79d8
  55eb27:	66 0f d6 06          	movq   QWORD PTR [esi],xmm0
  55eb2b:	89 4e 08             	mov    DWORD PTR [esi+0x8],ecx
  55eb2e:	66 8b 0d dc 79 5d 00 	mov    cx,WORD PTR ds:0x5d79dc
  55eb35:	66 89 4e 0c          	mov    WORD PTR [esi+0xc],cx
  55eb39:	8a 0d de 79 5d 00    	mov    cl,BYTE PTR ds:0x5d79de
  55eb3f:	88 4e 0e             	mov    BYTE PTR [esi+0xe],cl
  55eb42:	5f                   	pop    edi
  55eb43:	5e                   	pop    esi
  55eb44:	8b e5                	mov    esp,ebp
  55eb46:	5d                   	pop    ebp
  55eb47:	c3                   	ret
