# Minishell Tokenizer Documentation

## Overview

The tokenizer is a critical component of the minishell project that transforms raw command line input into structured tokens. These tokens are then processed by the parser and executor components to run commands.  
This document describes the tokenizer's functionality, implementation, and key features.

---

## Core Function

_split_line_to_tokens_

```c
t_token *split_line_to_tokens(char *str, char **env)
```

**Purpose:**  
Converts a raw command line string into a structured array of tokens with appropriate types.

**Parameters:**

- `str`: Raw command line input string
- `env`: Current environment variables array

**Return Value:**  
A pointer to a `t_token` structure containing:

- `size`: Number of tokens
- `type`: Array of token types (integers)
- `content`: Array of token content strings (`char*`)

---

## Tokenization Process

1. **Initial String Conversion**

   - Calls `convert_str(str)` to parse the input string.
   - Creates a linked list where each node represents a potential token.
   - Handles whitespace and basic token separation.

2. **Memory Allocation**

   - Allocates a `t_token` structure to store the final tokenized result.
   - Creates arrays for token content and types based on the token count.
   - Initializes tracking variables for the tokenization process.

3. **Token Processing**

   - Processes each item in the linked list via `lst_to_tokens`.
   - Extracts the text content for each token.
   - Prepares tokens for type classification.

4. **Type Classification**
   - Classifies each token with `set_type` into categories:

<table>
   <tr>
      <th>Token Type</th>
      <th>Description</th>
      <th>Examples</th>
   </tr>
   <tr>
      <td>Operators</td>
      <td>Shell operation symbols</td>
      <td>`</td>
   </tr>
   <tr>
      <td>Delimiters</td>
      <td>Special symbols</td>
      <td>( , ) , ; , : </td>
   </tr>
   <tr>
      <td>Built-ins</td>
      <td>Shell built-in commands</td>
      <td>echo, cd, pwd, exit, export, env, unset</td>
   </tr>
   <tr>
      <td>Executables</td>
      <td>External commands</td>
      <td>Any command found in PATH</td>
   </tr>
   <tr>
      <td>Flags</td>
      <td>Command options</td>
      <td>-l, --help</td>
   </tr>
   <tr>
      <td>Text</td>
      <td>Regular string arguments</td>
      <td>Any other text</td>
   </tr>
</table>

5. **String Handling**

   - Special processing for quoted strings:
     - **Single quotes (`'...'`)**: Treated as literal strings (`STR`).
     - **Double quotes (`"..."`)**: Treated as expandable strings (`EXPAND_STR`).
   - Quote characters are removed from the final token content.
   - Environment variables inside expandable strings are identified for later processing.

6. **Resource Management**
   - Cleans up the intermediate linked list structure.
   - Returns the complete token structure ready for parsing.

---

## Key Features

- **Quote Handling:** Properly differentiates between quoted and unquoted text.
- **Command Resolution:** Identifies executable commands by checking against `PATH`.
- **Operator Recognition:** Correctly identifies shell operators like pipes and redirects.
- **Built-in Support:** Special handling for shell built-in commands.
- **Memory Management:** Efficient allocation and cleanup of resources.

---

## Implementation Notes

The tokenizer forms the foundation of the shell's command processing pipeline, enabling interpretation of complex command syntax including:

- Command pipelines
- I/O redirections
- Variable expansions
- Quoted strings
- Command substitutions

This structured token output is then passed to the parser for further processing into an abstract syntax tree (AST).

---
