# Generazione Certificato di Sviluppo per Code Signing

## Perché serve?
Per firmare il plugin audio VST3/AU su macOS durante lo sviluppo locale.

## ⚠️ Sicurezza
**NON** committare mai su Git i file:
- `key.pem` (chiave privata)
- `cert.pem` (certificato)

Questi file sono già esclusi nel `.gitignore` del repository principale.

## Generazione Nuova Coppia Chiave/Certificato

### Opzione 1: Certificato Auto-Firmato (Development)

```bash
# Genera chiave privata RSA 4096-bit
openssl genrsa -out key.pem 4096

# Genera certificato auto-firmato valido per 1 anno
openssl req -new -x509 -key key.pem -out cert.pem -days 365 \
  -subj "/C=IT/ST=Lazio/L=Rome/O=Dev/CN=DevCert"
```

### Opzione 2: Usa Certificato Apple Developer (Production)

Per distribuire pubblicamente il plugin:

1. Ottieni un certificato "Developer ID Application" da Apple Developer Portal
2. Usa `codesign` invece di certificati PEM:

```bash
codesign --deep --force --verify --verbose \
  --sign "Developer ID Application: Your Name (TEAM_ID)" \
  --options runtime \
  BricastiM7.vst3
```

## Verifica Certificato

```bash
# Visualizza info certificato
openssl x509 -in cert.pem -text -noout

# Verifica corrispondenza chiave/certificato
openssl x509 -noout -modulus -in cert.pem | openssl md5
openssl rsa -noout -modulus -in key.pem | openssl md5
# I due hash MD5 devono essere identici
```

## File Posizione

I file `key.pem` e `cert.pem` devono stare in:
- `/Users/mainenti/make_plugin_riverberi/BricastiM7_Clone/`

Oppure specificare il path negli script di build CMake/Xcode.
