import os
import re
import pandas as pd

ROOT_DIR = "./bounded"
OUTPUT_FILE = "summary.xlsx"


def extract(pattern, text, default=""):
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

    if best_objective and best_bound:
        try:
            if int(best_objective) == int(best_bound):
                optimal_found = "x"
        except ValueError:
            pass

    row = {
        "File": os.path.basename(filepath),
        "Problem": problem,
        "Time limit (s)": time_limit,
        "Worker count": worker_count,
        "Best bound": best_bound,
        "Best objective": best_objective,
        "Memory consumed (MB)": memory_consumed,
        "Time consumed (s)": time_consumed,
        "Optimal found": optimal_found
    }

    return row


def main():
    with pd.ExcelWriter(
        OUTPUT_FILE,
        engine="openpyxl"
    ) as writer:

        for folder in sorted(os.listdir(ROOT_DIR)):
            folder_path = os.path.join(ROOT_DIR, folder)

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

    print(f"Saved to {OUTPUT_FILE}")


if __name__ == "__main__":
    main()