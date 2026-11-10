
/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe:     file format pei-i386


Disassembly of section .text:

00405230 <.text+0x4230>:
  405230:	56                   	push   esi
  405231:	ba e4 cf 58 00       	mov    edx,0x58cfe4
  405236:	b1 02                	mov    cl,0x2
  405238:	e8 e3 25 0f 00       	call   0x4f7820
  40523d:	8b 15 3c bd 72 0a    	mov    edx,DWORD PTR ds:0xa72bd3c
  405243:	a1 34 1c 6d 0a       	mov    eax,ds:0xa6d1c34
  405248:	85 d2                	test   edx,edx
  40524a:	75 08                	jne    0x405254
  40524c:	85 c0                	test   eax,eax
  40524e:	0f 84 ea 00 00 00    	je     0x40533e
  405254:	50                   	push   eax
  405255:	b9 1b 00 00 00       	mov    ecx,0x1b
  40525a:	e8 d1 41 01 00       	call   0x419430
  40525f:	83 c4 04             	add    esp,0x4
  405262:	83 f8 ff             	cmp    eax,0xffffffff
  405265:	75 0b                	jne    0x405272
  405267:	b9 fc cf 58 00       	mov    ecx,0x58cffc
  40526c:	5e                   	pop    esi
  40526d:	e9                   	.byte 0xe9
  40526e:	9e                   	sahf
  40526f:	12                   	.byte 0x12
