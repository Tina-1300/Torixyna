# Torixyna::Registry Module

The `Torixyna::Registry` module provides a set of utilities for interacting with the Windows Registry. It allows developers to easily read, write, and manage registry keys and values, including various data types such as strings, DWORDs, binary data, and more. This module is designed to simplify registry operations and provide efficient access to registry-related tasks in Windows-based applications.

## Key Features:
- **Registry Management**: 
  - Write, read, and delete registry keys and values in different data formats such as `REG_SZ`, `REG_DWORD`, `REG_BINARY`, `REG_QWORD`, `REG_MULTI_SZ`, and `REG_EXPAND_SZ`.
  
- **Registry Size Info**: 
  - Retrieve the current size of the registry and the maximum allowed size.

- **Registry Value Type Info**: 
  - Get the type of a registry value and handle errors related to unknown value types.

- **System Configuration**: 
  - Manage system settings such as file extension visibility, hidden items visibility, checkbox status, and even set the system wallpaper.
