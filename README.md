# C++ Alliance Agent Demo

Test repository for the AI-powered C++ code review agent.

## What This Repo Is For

This repo receives webhook events that trigger the agent pipeline:
1. **Knowledge Agent** queries Pinecone for relevant C++ review patterns
2. **Coding Agent** implements fixes following LLVM coding standards
3. **Review Agent** validates changes before PR creation

## How To Trigger

Create an issue or comment mentioning `@cppalliance-bot` to trigger the agent.
