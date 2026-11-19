#!/usr/bin/env python3

"""
Prints the version of each dependency in the external directory, along with
its remote URL.
"""

import argparse
import json
import subprocess
from os import listdir
from pathlib import Path


def git(*args: str, cwd: Path) -> str:
    try:
        return (
            subprocess.run(
                ["git", *args],
                cwd=cwd,
                check=True,
                capture_output=True,
            )
            .stdout.decode("utf-8")
            .strip()
        )
    except (subprocess.CalledProcessError, OSError):
        return "N/A"


def print_text(deps: list[tuple[str, str, str, str]]) -> None:
    for dep, version, commit, remote in deps:
        print(f"{dep}\t{version}\t{commit}\t{remote}")


def print_markdown(deps: list[tuple[str, str, str, str]]) -> None:
    def print_row(*args: tuple[str, int]) -> None:
        print(f"| {' | '.join(f'{arg[0]:<{arg[1]}}' for arg in args)} |")

    dl = max(len(dep[0]) for dep in deps)
    vl = max(len(dep[1]) for dep in deps)
    cl = max(len(dep[2]) for dep in deps)
    rl = max(len(dep[3]) for dep in deps)

    print_row(("Dependency", dl), ("Version", vl), ("Commit", cl), ("Remote", rl))
    print_row(("-" * dl, dl), ("-" * vl, vl), ("-" * cl, cl), ("-" * rl, rl))

    for dep, version, commit, remote in deps:
        print_row((dep, dl), (version, vl), (commit, cl), (remote, rl))


def print_json(deps: list[tuple[str, str, str, str]]) -> None:
    print(
        json.dumps(
            [
                {
                    "dependency": dep,
                    "version": version,
                    "commit": commit,
                    "remote": remote,
                }
                for dep, version, commit, remote in deps
            ],
            indent=2,
        )
    )


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Print the version of each dependency in the external directory."
    )
    parser.add_argument(
        "-f",
        "--format",
        help="Specify the output format",
        choices=["text", "md", "json"],
        default="text",
    )

    args = parser.parse_args()

    root_dir = Path(__file__).parent.parent / "external"

    deps: list[tuple[str, str, str, str]] = []

    for dependency in sorted(listdir(root_dir)):
        dependency_root = root_dir / dependency

        commit = git("rev-parse", "--short", "HEAD", cwd=dependency_root)
        version = git("describe", "--tags", "--exact-match", cwd=dependency_root)
        remote = git("remote", "get-url", "origin", cwd=dependency_root)

        if version == "N/A":
            version = commit

        deps.append((dependency, version, commit, remote))

    match args.format:
        case "text":
            print_text(deps)
        case "md":
            print_markdown(deps)
        case "json":
            print_json(deps)
        case _:
            raise ValueError(f"Unsupported format: {args.format}")


if __name__ == "__main__":
    main()
