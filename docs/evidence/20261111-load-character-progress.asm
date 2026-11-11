
/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

0057e4c0 <.text+0x17d4c0>:
  57e4c0:	55                   	push   ebp
  57e4c1:	8b ec                	mov    ebp,esp
  57e4c3:	b8 1c 10 00 00       	mov    eax,0x101c
  57e4c8:	e8 03 cc 00 00       	call   0x58b0d0
  57e4cd:	a1 0c 20 5e 00       	mov    eax,ds:0x5e200c
  57e4d2:	33 c5                	xor    eax,ebp
  57e4d4:	89 45 fc             	mov    DWORD PTR [ebp-0x4],eax
  57e4d7:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  57e4dc:	53                   	push   ebx
  57e4dd:	56                   	push   esi
  57e4de:	57                   	push   edi
  57e4df:	8b 3d f8 c1 58 00    	mov    edi,DWORD PTR ds:0x58c1f8
  57e4e5:	6a 78                	push   0x78
  57e4e7:	6a 58                	push   0x58
  57e4e9:	6a 38                	push   0x38
  57e4eb:	ff 70 04             	push   DWORD PTR [eax+0x4]
  57e4ee:	c7 05 24 41 78 0a 01 	mov    DWORD PTR ds:0xa784124,0x1
  57e4f5:	00 00 00 
  57e4f8:	c7 05 94 2c 5e 00 00 	mov    DWORD PTR ds:0x5e2c94,0x0
  57e4ff:	00 00 00 
  57e502:	ff d7                	call   edi
  57e504:	50                   	push   eax
  57e505:	68 00 10 00 00       	push   0x1000
  57e50a:	68 16 c6 58 00       	push   0x58c616
  57e50f:	6a 7d                	push   0x7d
  57e511:	68 b4 00 00 00       	push   0xb4
  57e516:	ba 50 00 00 00       	mov    edx,0x50
  57e51b:	b9 62 02 00 00       	mov    ecx,0x262
  57e520:	e8 4b 7d f9 ff       	call   0x516270
  57e525:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  57e52a:	83 c4 24             	add    esp,0x24
  57e52d:	6a 01                	push   0x1
  57e52f:	68 ab 00 00 00       	push   0xab
  57e534:	68 ab 00 00 00       	push   0xab
  57e539:	68 ab 00 00 00       	push   0xab
  57e53e:	ff 70 04             	push   DWORD PTR [eax+0x4]
  57e541:	ff d7                	call   edi
  57e543:	83 c4 10             	add    esp,0x10
  57e546:	ba 5f 00 00 00       	mov    edx,0x5f
  57e54b:	b9 67 02 00 00       	mov    ecx,0x267
  57e550:	50                   	push   eax
  57e551:	68 2c c6 5d 00       	push   0x5dc62c
  57e556:	e8 45 00 f9 ff       	call   0x50e5a0
  57e55b:	8b 1d 7c c2 58 00    	mov    ebx,DWORD PTR ds:0x58c27c
  57e561:	83 c4 0c             	add    esp,0xc
  57e564:	83 3d 5c ba 5b 06 00 	cmp    DWORD PTR ds:0x65bba5c,0x0
  57e56b:	75 3e                	jne    0x57e5ab
  57e56d:	e8 1e ca f8 ff       	call   0x50af90
  57e572:	83 3d d8 bc 5b 06 00 	cmp    DWORD PTR ds:0x65bbcd8,0x0
  57e579:	74 17                	je     0x57e592
  57e57b:	e8 c0 1a f9 ff       	call   0x510040
  57e580:	a1 d8 bc 5b 06       	mov    eax,ds:0x65bbcd8
  57e585:	33 c9                	xor    ecx,ecx
  57e587:	83 f8 02             	cmp    eax,0x2
  57e58a:	0f 44 c1             	cmove  eax,ecx
  57e58d:	a3 d8 bc 5b 06       	mov    ds:0x65bbcd8,eax
  57e592:	e8 29 ce f8 ff       	call   0x50b3c0
  57e597:	83 3d 54 1c 5c 0a 00 	cmp    DWORD PTR ds:0xa5c1c54,0x0
  57e59e:	75 0b                	jne    0x57e5ab
  57e5a0:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  57e5a6:	ff d3                	call   ebx
  57e5a8:	83 c4 04             	add    esp,0x4
  57e5ab:	68 a4 2c 00 00       	push   0x2ca4
  57e5b0:	6a 00                	push   0x0
  57e5b2:	68 58 f5 17 02       	push   0x217f558
  57e5b7:	c7 05 d4 22 61 0a 00 	mov    DWORD PTR ds:0xa6122d4,0x0
  57e5be:	00 00 00 
  57e5c1:	c7 05 b0 22 61 0a 00 	mov    DWORD PTR ds:0xa6122b0,0x0
  57e5c8:	00 00 00 
  57e5cb:	c7 05 84 1f 61 0a 00 	mov    DWORD PTR ds:0xa611f84,0x0
  57e5d2:	00 00 00 
  57e5d5:	c7 05 70 28 61 0a 00 	mov    DWORD PTR ds:0xa612870,0x0
  57e5dc:	00 00 00 
  57e5df:	c7 05 1c 2c 5e 00 18 	mov    DWORD PTR ds:0x5e2c1c,0xfffffc18
  57e5e6:	fc ff ff 
  57e5e9:	e8 72 c8 00 00       	call   0x58ae60
  57e5ee:	83 c4 0c             	add    esp,0xc
  57e5f1:	c7 05 a4 6a 6c 0a 00 	mov    DWORD PTR ds:0xa6c6aa4,0x0
  57e5f8:	00 00 00 
  57e5fb:	c7 05 3c 6a 6c 0a 00 	mov    DWORD PTR ds:0xa6c6a3c,0x0
  57e602:	00 00 00 
  57e605:	6a 64                	push   0x64
  57e607:	6a 00                	push   0x0
  57e609:	68 38 1c 6d 0a       	push   0xa6d1c38
  57e60e:	e8 4d c8 00 00       	call   0x58ae60
  57e613:	83 c4 0c             	add    esp,0xc
  57e616:	6a 64                	push   0x64
  57e618:	6a 00                	push   0x0
  57e61a:	68 d0 1b 6d 0a       	push   0xa6d1bd0
  57e61f:	e8 3c c8 00 00       	call   0x58ae60
  57e624:	83 c4 0c             	add    esp,0xc
  57e627:	68 80 0c 00 00       	push   0xc80
  57e62c:	6a 00                	push   0x0
  57e62e:	68 58 cd 34 06       	push   0x634cd58
  57e633:	e8 28 c8 00 00       	call   0x58ae60
  57e638:	83 c4 0c             	add    esp,0xc
  57e63b:	c7 05 44 d1 35 06 00 	mov    DWORD PTR ds:0x635d144,0x0
  57e642:	00 00 00 
  57e645:	c6 05 f2 f4 18 05 01 	mov    BYTE PTR ds:0x518f4f2,0x1
  57e64c:	c6 05 d3 4e 78 02 00 	mov    BYTE PTR ds:0x2784ed3,0x0
  57e653:	c7 05 f0 10 61 0a 00 	mov    DWORD PTR ds:0xa6110f0,0x0
  57e65a:	00 00 00 
  57e65d:	e8 de f4 fe ff       	call   0x56db40
  57e662:	e8 a9 ea fe ff       	call   0x56d110
  57e667:	68 40 7e 05 00       	push   0x57e40
  57e66c:	6a 00                	push   0x0
  57e66e:	68 a8 28 6d 0a       	push   0xa6d28a8
  57e673:	e8 e8 c7 00 00       	call   0x58ae60
  57e678:	83 c4 0c             	add    esp,0xc
  57e67b:	e8 c0 e5 fe ff       	call   0x56cc40
  57e680:	a1 a8 b7 84 0a       	mov    eax,ds:0xa84b7a8
  57e685:	40                   	inc    eax
  57e686:	25 ff 03 00 80       	and    eax,0x800003ff
  57e68b:	79 07                	jns    0x57e694
  57e68d:	48                   	dec    eax
  57e68e:	0d 00 fc ff ff       	or     eax,0xfffffc00
  57e693:	40                   	inc    eax
  57e694:	a3 a8 b7 84 0a       	mov    ds:0xa84b7a8,eax
  57e699:	c1 e0 0a             	shl    eax,0xa
  57e69c:	68 00 04 00 00       	push   0x400
  57e6a1:	6a 00                	push   0x0
  57e6a3:	8d b0 b0 1e 94 0a    	lea    esi,[eax+0xa941eb0]
  57e6a9:	56                   	push   esi
  57e6aa:	e8 b1 c7 00 00       	call   0x58ae60
  57e6af:	83 c4 0c             	add    esp,0xc
  57e6b2:	68 f6 a6 72 0a       	push   0xa72a6f6
  57e6b7:	68 e8 a6 72 0a       	push   0xa72a6e8
  57e6bc:	68 80 c6 58 00       	push   0x58c680
  57e6c1:	56                   	push   esi
  57e6c2:	e8 09 2a e8 ff       	call   0x4010d0
  57e6c7:	56                   	push   esi
  57e6c8:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  57e6ce:	68 40 c6 5d 00       	push   0x5dc640
  57e6d3:	50                   	push   eax
  57e6d4:	e8 f7 29 e8 ff       	call   0x4010d0
  57e6d9:	83 c4 1c             	add    esp,0x1c
  57e6dc:	8d 95 f8 fb ff ff    	lea    edx,[ebp-0x408]
  57e6e2:	b9 01 00 00 00       	mov    ecx,0x1
  57e6e7:	e8 14 3c fe ff       	call   0x562300
  57e6ec:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  57e6f1:	6a 01                	push   0x1
  57e6f3:	68 ff 00 00 00       	push   0xff
  57e6f8:	68 ff 00 00 00       	push   0xff
  57e6fd:	68 ff 00 00 00       	push   0xff
  57e702:	ff 70 04             	push   DWORD PTR [eax+0x4]
  57e705:	ff d7                	call   edi
  57e707:	83 c4 10             	add    esp,0x10
  57e70a:	ba 73 00 00 00       	mov    edx,0x73
  57e70f:	b9 67 02 00 00       	mov    ecx,0x267
  57e714:	50                   	push   eax
  57e715:	6a 1e                	push   0x1e
  57e717:	68 aa 00 00 00       	push   0xaa
  57e71c:	e8 1f 04 f9 ff       	call   0x50eb40
  57e721:	83 c4 10             	add    esp,0x10
  57e724:	83 3d 5c ba 5b 06 00 	cmp    DWORD PTR ds:0x65bba5c,0x0
  57e72b:	75 3e                	jne    0x57e76b
  57e72d:	e8 5e c8 f8 ff       	call   0x50af90
  57e732:	83 3d d8 bc 5b 06 00 	cmp    DWORD PTR ds:0x65bbcd8,0x0
  57e739:	74 17                	je     0x57e752
  57e73b:	e8 00 19 f9 ff       	call   0x510040
  57e740:	a1 d8 bc 5b 06       	mov    eax,ds:0x65bbcd8
  57e745:	33 c9                	xor    ecx,ecx
  57e747:	83 f8 02             	cmp    eax,0x2
  57e74a:	0f 44 c1             	cmove  eax,ecx
  57e74d:	a3 d8 bc 5b 06       	mov    ds:0x65bbcd8,eax
  57e752:	e8 69 cc f8 ff       	call   0x50b3c0
  57e757:	83 3d 54 1c 5c 0a 00 	cmp    DWORD PTR ds:0xa5c1c54,0x0
  57e75e:	75 0b                	jne    0x57e76b
  57e760:	ff 35 cc 10 61 0a    	push   DWORD PTR ds:0xa6110cc
  57e766:	ff d3                	call   ebx
  57e768:	83 c4 04             	add    esp,0x4
  57e76b:	f3 0f 10 15 1c bd 72 	movss  xmm2,DWORD PTR ds:0xa72bd1c
  57e772:	0a 
  57e773:	0f 2e 15 70 d0 5d 00 	ucomiss xmm2,DWORD PTR ds:0x5dd070
  57e77a:	9f                   	lahf
  57e77b:	f6 c4 44             	test   ah,0x44
  57e77e:	7b 0d                	jnp    0x57e78d
  57e780:	f3 0f 11 15 c8 b5 5b 	movss  DWORD PTR ds:0x65bb5c8,xmm2
  57e787:	06 
  57e788:	e8 b3 6f f7 ff       	call   0x4f5740
  57e78d:	a1 00 b9 72 0a       	mov    eax,ds:0xa72b900
  57e792:	3d 3e 01 00 00       	cmp    eax,0x13e
  57e797:	0f 8c 0c 17 00 00    	jl     0x57fea9
  57e79d:	3d 5e 01 00 00       	cmp    eax,0x15e
  57e7a2:	7d 14                	jge    0x57e7b8
  57e7a4:	c7 05 60 ac 72 0a 00 	mov    DWORD PTR ds:0xa72ac60,0x0
  57e7ab:	00 00 00 
  57e7ae:	c7 05 64 ac 72 0a 00 	mov    DWORD PTR ds:0xa72ac64,0x0
  57e7b5:	00 00 00 
  57e7b8:	e8 c3 98 e8 ff       	call   0x408080
  57e7bd:	b9 10 3c 78 0a       	mov    ecx,0xa783c10
  57e7c2:	e8 09 24 e9 ff       	call   0x410bd0
  57e7c7:	e8 04 dd e9 ff       	call   0x41c4d0
  57e7cc:	e8 9f 56 f2 ff       	call   0x4a3e70
  57e7d1:	e8 ba d6 f0 ff       	call   0x48be90
  57e7d6:	e8 d5 c2 f1 ff       	call   0x49aab0
  57e7db:	e8 80 64 fa ff       	call   0x524c60
  57e7e0:	68 90 3c 78 0a       	push   0xa783c90
  57e7e5:	8d 85 f8 fb ff ff    	lea    eax,[ebp-0x408]
  57e7eb:	68 c4 8d 59 00       	push   0x598dc4
  57e7f0:	50                   	push   eax
  57e7f1:	e8 da 28 e8 ff       	call   0x4010d0
  57e7f6:	83 c4 0c             	add    esp,0xc
  57e7f9:	8d 85 f8 f3 ff ff    	lea    eax,[ebp-0xc08]
  57e7ff:	68 90 3c 78 0a       	push   0xa783c90
  57e804:	68 30 fc 5a 00       	push   0x5afc30
  57e809:	50                   	push   eax
  57e80a:	e8 c1 28 e8 ff       	call   0x4010d0
  57e80f:	83 c4 0c             	add    esp,0xc
  57e812:	8d 95 f8 f3 ff ff    	lea    edx,[ebp-0xc08]
  57e818:	8d 8d f8 fb ff ff    	lea    ecx,[ebp-0x408]
  57e81e:	e8 fd 54 f5 ff       	call   0x4d3d20
  57e823:	a1 10 bb 5b 06       	mov    eax,ds:0x65bbb10
  57e828:	6a 01                	push   0x1
  57e82a:	6a 54                	push   0x54
  57e82c:	68 fc 00 00 00       	push   0xfc
  57e831:	68 fc 00 00 00       	push   0xfc
  57e836:	ff 70 04             	push   DWORD PTR [eax+0x4]
  57e839:	ff d7                	call   edi
  57e83b:	83 c4 10             	add    esp,0x10
  57e83e:	ba 91 00 00 00       	mov    edx,0x91
  57e843:	b9 67 02 00 00       	mov    ecx,0x267
  57e848:	50                   	push   eax
  57e849:	68 a8 c6 5d 00       	push   0x5dc6a8
  57e84e:	e8 4d fd f8 ff       	call   0x50e5a0
  57e853:	83 c4 0c             	add    esp,0xc
  57e856:	e8 c5 ce f8 ff       	call   0x50b720
  57e85b:	b9 01 00 00 00       	mov    ecx,0x1
  57e860:	e8 3b f1 f8 ff       	call   0x50d9a0
  57e865:	e8 66 cf f7 ff       	call   0x4fb7d0
