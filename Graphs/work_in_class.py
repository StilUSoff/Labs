import matplotlib.pyplot as plt
import networkx as nx

# Создаем граф
G = nx.Graph()

# Добавляем узлы
nodes = [1, 2, 3, 4, 5, 6]
G.add_nodes_from(nodes)

# Добавляем ребра
edges = [(x, y) for x in nodes for y in nodes if x + y <= 7 and x != y]
G.add_edges_from(edges)

# Рисуем граф
pos = nx.spring_layout(G)  # Определяем позиции узлов для красивого размещения
nx.draw(G, pos, with_labels=True, node_color='skyblue', node_size=1500, font_size=10, font_weight='bold')
plt.title("Граф отношения $x + y \leq 7$")
plt.show()
