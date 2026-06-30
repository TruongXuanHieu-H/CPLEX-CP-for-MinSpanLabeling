import os
import re
import argparse
import pandas as pd


def extract(pattern, text, default="-"):
    m = re.search(pattern, text, re.MULTILINE)
    return m.group(1).strip() if m else default


def parse_log(filepath):
    with open(filepath, "r", encoding="utf-8", errors="ignore") as f:
        content = f.read()

    problem_path = extract(
        r'! Solving for graph\s+([^\n\r]+)',
        content
    )

    problem = os.path.basename(problem_path)

    time_limit = extract(
        r'!\s*TimeLimit\s*=\s*(\d+)',
        content
    )

    worker_count = extract(
        r'! Using parallel search with (\d+) workers\.',
        content
    )

    target_value = extract(
        r'!\s*Target value is set to\s*(\d+)',
        content
    )

    lower_bound = extract(
        r'!\s*Lower bound is set to\s*(\d+)',
        content
    )

    upper_bound = extract(
        r'!\s*Upper bound is set to\s*(\d+)',
        content
    )

    best_objective = extract(
        r'!\s*Best objective\s*:\s*(\d+)',
        content
    )

    best_bound = extract(
        r'!\s*Best bound\s*:\s*(\d+)',
        content
    )

    memory_consumed = extract(
        r'!\s*Total memory usage\s*:\s*([\d.]+)\s*MB',
        content
    )

    time_consumed = extract(
        r'!\s*Time spent in solve\s*:\s*([\d.]+)s',
        content
    )

    optimal_found = ""

    if best_objective != "-" and best_bound != "-":
        try:
            if int(best_objective) == int(best_bound):
                optimal_found = "x"
        except ValueError:
            pass

    return {
        "File": os.path.basename(filepath),
        "Problem": problem,
        "Time limit (s)": time_limit,
        "Worker count": worker_count,
        "Target value": target_value,
        "Lower bound": lower_bound,
        "Upper bound": upper_bound,
        "Best bound": best_bound,
        "Best objective": best_objective,
        "Memory consumed (MB)": memory_consumed,
        "Time consumed (s)": time_consumed,
        "Optimal found": optimal_found
    }


def main(root_dir, output_file):
    with pd.ExcelWriter(
        output_file,
        engine="openpyxl"
    ) as writer:

        for folder in sorted(os.listdir(root_dir)):
            folder_path = os.path.join(root_dir, folder)

            if not os.path.isdir(folder_path):
                continue

            rows = []

            for filename in sorted(os.listdir(folder_path)):
                if not filename.endswith(".txt"):
                    continue

                filepath = os.path.join(folder_path, filename)

                try:
                    rows.append(parse_log(filepath))
                except Exception as e:
                    print(f"Error parsing {filepath}: {e}")

            if not rows:
                continue

            df = pd.DataFrame(rows)

            columns = [
                "File",
                "Problem",
                "Time limit (s)",
                "Worker count",
                "Target value",
                "Lower bound",
                "Upper bound",
                "Best bound",
                "Best objective",
                "Memory consumed (MB)",
                "Time consumed (s)",
                "Optimal found"
            ]

            df = df[columns]

            sheet_name = folder[:31]

            df.to_excel(
                writer,
                sheet_name=sheet_name,
                index=False
            )

    print(f"Saved to {output_file}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Parse CPLEX-CP logs into an Excel summary."
    )

    parser.add_argument(
        "root_dir",
        help="Root directory containing experiment folders"
    )

    parser.add_argument(
        "output_file",
        help="Output Excel file"
    )

    args = parser.parse_args()

    main(args.root_dir, args.output_file)