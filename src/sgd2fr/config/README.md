# SGD2FreeRes - Configuration

This library is designed to handle all operations related to the reading and writing of configuration files. Any field that is missing is automatically assigned the default value. The library also handles the parsing of old versions and outputting into any new format. Any missing field is assigned the default value for that field.

The handling of resolution logic, such as filtering and selection, is outside of the scope of this library.

## Formats

### Current (Version 2) JSON Format (3.0.5.0 and above)

This JSON config layout was created in response to the difficulty of handling the old format. Below is an example config file.

```json
{
    "!!!Metadata (Do not modify)!!!": {
        "Config Version": "3.1.0.0"
    },
    "Config Tab Width": 4,
    "Custom MPQ File": "SGD2FreeRes.mpq",
    "Ingame Resolution": "1024x768",
    "Ingame Resolutions": [
        "640x480",
        "800x600",
        "1024x768"
    ],
    "Main Menu Resolution": "800x600",
}
```

The following options have been removed, because they were rarely used:

- Enable Screen Border Frame?
- Use Original Screen Border Frame?
- Use 800 Interface Bar?

These are options that are deemed out of scope for this project. They are more appropriate for a UI customization project.

### Deprecated Version 1 JSON Format (3.0.4.X and below)

The JSON config layout was designed on-the-fly, adding elements new elements as-needed. It was also designed under the assumption that other DLLs might share the same config file. Below is an example config file.

```json
{
    "SlashGaming Diablo II Free Resolution": {
        "!!!Metadata (Do not modify)!!!": {
            "Major Version A": 3,
            "Major Version B": 0,
            "Minor Version A": 1,
            "Minor Version B": 0
        },
        "Ingame Resolutions": [
            "640x480",
            "800x600",
            "1024x768"
        ],
        "Ingame Resolution Mode": 2,
        "Main Menu Resolution": "800x600",
        "Custom MPQ File": "SGD2FreeRes.mpq",
        "Enable Screen Border Frame?": true,
        "Use Original Screen Border Frame?": false,
        "Use 800 Interface Bar?": true
    },
    "!!!Globals!!!": {
        "Config Tab Width": 4
    }
}
```
