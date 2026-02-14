import tkinter as tk
from tkinter import messagebox

FILE_NAME = "customers.txt"
customers = []

# ---------------- FILE HANDLING ----------------

def load_from_file():
    customers.clear()
    try:
        with open(FILE_NAME, "r") as f:
            for line in f:
                name, phone, usage, bill = line.strip().split(",")
                customers.append([name, phone, float(usage), float(bill)])
    except FileNotFoundError:
        pass

def save_to_file():
    with open(FILE_NAME, "w") as f:
        for c in customers:
            f.write(f"{c[0]},{c[1]},{c[2]},{c[3]}\n")

# ---------------- CORE FUNCTIONS ----------------

def add_record():
    name = name_entry.get()
    phone = phone_entry.get()
    usage = usage_entry.get()

    if name == "" or phone == "" or usage == "":
        messagebox.showerror("Error", "All fields required")
        return

    for c in customers:
        if c[1] == phone:
            messagebox.showerror("Error", "Phone already exists")
            return

    usage = float(usage)
    bill = usage * 0.1
    customers.append([name, phone, usage, bill])
    save_to_file()
    messagebox.showinfo("Success", "Record Added")
    clear_fields()

def view_records():
    output.delete(1.0, tk.END)
    output.insert(tk.END, "Name\tPhone\tUsage\tBill\n")
    output.insert(tk.END, "-"*50 + "\n")
    for c in customers:
        output.insert(tk.END, f"{c[0]}\t{c[1]}\t{c[2]}\t{c[3]}\n")

def modify_record():
    phone = phone_entry.get()
    new_usage = usage_entry.get()

    if phone == "" or new_usage == "":
        messagebox.showerror("Error", "Phone and Usage required")
        return

    for i in range(len(customers)):
        if customers[i][1] == phone:
            new_usage = float(new_usage)
            customers[i][2] = new_usage
            customers[i][3] = new_usage * 0.1
            save_to_file()
            messagebox.showinfo("Success", "Record Modified")
            clear_fields()
            return

    messagebox.showerror("Error", "Record Not Found")

def delete_record():
    phone = phone_entry.get()

    if phone == "":
        messagebox.showerror("Error", "Phone required")
        return

    for c in customers:
        if c[1] == phone:
            customers.remove(c)
            save_to_file()
            messagebox.showinfo("Success", "Record Deleted")
            clear_fields()
            return

    messagebox.showerror("Error", "Record Not Found")

def view_payment():
    phone = phone_entry.get()

    if phone == "":
        messagebox.showerror("Error", "Phone required")
        return

    for c in customers:
        if c[1] == phone:
            messagebox.showinfo(
                "Payment Details",
                f"Name: {c[0]}\nPhone: {c[1]}\nUsage: {c[2]}\nBill: {c[3]}"
            )
            return

    messagebox.showerror("Error", "Record Not Found")

def clear_fields():
    name_entry.delete(0, tk.END)
    phone_entry.delete(0, tk.END)
    usage_entry.delete(0, tk.END)

# ---------------- GUI ----------------

root = tk.Tk()
root.title("Telecom Billing System")
root.geometry("500x500")

tk.Label(root, text="Telecom Billing System", font=("Arial", 16, "bold")).pack()

frame = tk.Frame(root)
frame.pack(pady=10)

tk.Label(frame, text="Name").grid(row=0, column=0)
tk.Label(frame, text="Phone").grid(row=1, column=0)
tk.Label(frame, text="Usage").grid(row=2, column=0)

name_entry = tk.Entry(frame)
phone_entry = tk.Entry(frame)
usage_entry = tk.Entry(frame)

name_entry.grid(row=0, column=1)
phone_entry.grid(row=1, column=1)
usage_entry.grid(row=2, column=1)

btn_frame = tk.Frame(root)
btn_frame.pack(pady=10)

tk.Button(btn_frame, text="Add", width=12, command=add_record).grid(row=0, column=0)
tk.Button(btn_frame, text="View All", width=12, command=view_records).grid(row=0, column=1)
tk.Button(btn_frame, text="Modify", width=12, command=modify_record).grid(row=1, column=0)
tk.Button(btn_frame, text="Delete", width=12, command=delete_record).grid(row=1, column=1)
tk.Button(btn_frame, text="View Payment", width=12, command=view_payment).grid(row=2, column=0)
tk.Button(btn_frame, text="Clear", width=12, command=clear_fields).grid(row=2, column=1)

output = tk.Text(root, height=12, width=55)
output.pack(pady=10)

load_from_file()
root.mainloop()
