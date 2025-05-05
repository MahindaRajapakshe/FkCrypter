# FkCrypter

**FkCrypter** is a secure string decryption module for Android that uses the [XXTEA](https://en.wikipedia.org/wiki/XXTEA) algorithm implemented in native C++ via JNI. This approach is designed to obfuscate and protect sensitive data (like API keys, messages, etc.) by keeping the encryption logic out of Java and only exposing decryption functionality in native code.

---

## 🔐 Features

- ✅ Native-only decryption (encryption logic excluded for security)
- ✅ Based on the XXTEA block cipher (128-bit key)
- ✅ Lightweight and efficient
- ✅ Clean JNI bridge between Java and C++
- ✅ Easy to integrate into any Android app

---

## 🛠 Setup & Usage

### 1. Add JNI files to your project

Include the following files under `cpp/` or `src/main/cpp/`:

- `xxtea.h`
- `xxtea.cpp` (only decryption method)
- `native-lib.cpp`

Make sure to update your `CMakeLists.txt` accordingly.

### 2. Java Class: `FkCrypter.java`

```java
public class FkCrypter {

    static {
        System.loadLibrary("kakuluwa");
    }

    public static native byte[] decryptWithXXTEA(byte[] encryptedData);
}
