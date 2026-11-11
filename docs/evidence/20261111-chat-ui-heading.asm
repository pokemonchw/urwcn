
/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

004f8f80 <.text+0xf7f80>:
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
