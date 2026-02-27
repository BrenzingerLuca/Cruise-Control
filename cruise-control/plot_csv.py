import pandas as pd
import matplotlib.pyplot as plt

# Get filename
print("Enter the filename: ")
filename = str(input())
print("Plotting: ", filename)

# Read csv as pd dataframe
df = pd.read_csv("data/" + filename)

if len(df.columns) < 2:
    raise ValueError("Your csv file must contain at least two columns")
x_Axis, y_Axis = df.columns[:2]

# Plot the data
plt.figure()
plt.plot(df[x_Axis], df[y_Axis])
plt.xlabel(x_Axis)
plt.ylabel(y_Axis)
plt.title(f"{y_Axis} vs {x_Axis}")
plt.grid(True)
plt.show()

#workaround in case popup window is not working in WSL
#plt.savefig('cruise_plot.png')
#print("Plot saved as cruise_plot.png")




