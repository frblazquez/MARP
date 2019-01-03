package ucm.fdi.marp;

public class SplayTree<T extends Comparable<T>>
{
	protected Node root;

	protected class Node
	{
		private T    elem;
		private Node left;
		private Node right;
		private Node parent;

		public Node(Node l, T e, Node r, Node p)
		{
			left   = l;
			elem   = e;
			right  = r;
			parent = p;
		}
	}

	public void stupid_test()
	{
		if(root == null)
			System.out.println("La raíz es nula");
		else if(root.left == null)
			System.out.println("La raiz no tiene hijo izquierdo");
	}


	public SplayTree()
	{
		root  = null;
	}
	public boolean empty()
	{
		return root == null;
	}
	public boolean insert(T elem)
	{
	  Node father = null;
	  Node node = root;

	  while(node != null)
	  {
	    father = node;

	         if(elem.compareTo(node.elem) < 0)     node = node.left;
	    else if(elem.compareTo(node.elem) > 0)     node = node.right;
	    else {splay(node); return false;} // The element is already in the tree
	  }

	  node = new Node(null, elem, null, father);

	  if(father != null)
	    {if(elem.compareTo(father.elem)<0) father.left = node;
	     else                          	   father.right= node;}
	  else
	    root = node;

	  splay(node);  return true;

	}
	public boolean find(T elem)
	{
	  Node father = null;
	  Node node   = root;

	  while(node != null)
	  {
	    father = node;

	         if(elem.compareTo(node.elem) < 0)     node = node.left;
	    else if(elem.compareTo(node.elem) > 0)     node = node.right;
	    else {splay(node); return true;} // The element is already in the tree
	  }

	  if(father != null)
		  splay(father);

	  return false;
	}
	public boolean erase(T elem)
	{
		return false;
	}

	protected void splay(Node node)
	{
		if(node == null)
		    throw new NullPointerException("Splay over null node!");
		  while(node.parent != null)
		  {
		    if(node.parent.parent == null)  //Direct child from root!
		    {
		      if(node.parent.left == node)  rotateRight(node.parent);
		      else                          rotateLeft(node.parent);
		    }
		    else                       //Node has grandfather
		    {
		      Node grandParent = node.parent.parent;

		      if(grandParent.left != null       && node == grandParent.left.left)    //Zig-zig
		       {rotateRight(grandParent);
		        rotateRight(node.parent);}
		      else if(grandParent.right != null && node == grandParent.right.right)  //Zag-zag
		        {rotateLeft(grandParent);
		         rotateLeft(node.parent);}
		      else if(grandParent.left  != null  && node == grandParent.left.right)   //Zag-Zig
		      	{rotateLeft(node.parent);
		         rotateRight(grandParent);}
		      else if(grandParent.right != null && node == grandParent.right.left)   //Zig-zag
		        {rotateRight(node.parent);
		         rotateLeft(grandParent);}
		      else
		        throw new IllegalStateException("Illegal state reached during splay operation!");
		    }
		  }
	}
	protected void rotateRight(Node node)
	{
		if(node == null)
		    throw new NullPointerException("Right rotation over null node!");

		  Node father    = node.parent;   //Father
		  Node leftChild = node.left;     //Left child

		  if(leftChild != null)
		  {
		    node.left        = leftChild.right;
		    node.parent      = leftChild;
		    leftChild.parent = father;
		    leftChild.right  = node;

		    if(node.left != null)  node.left.parent = node;
		    if(father    != null)
		      {if(node == father.left)  father.left = leftChild;
		       else                     father.right= leftChild;}
		    else
		      root = leftChild;
		  }
	}
	protected void rotateLeft(Node node)
	{
		  if(node == null)
			    throw new NullPointerException("Left rotation over null node!");

		  Node father     = node.parent;    //Father
		  Node rightChild = node.right;     //Right child

		  if(rightChild != null)
		  {
		    node.right        = rightChild.left;
		    node.parent       = rightChild;
		    rightChild.parent = father;
		    rightChild.left   = node;

		    if(node.right != null)  node.right.parent = node;
		    if(father      != null)
		      {if(node == father.left)  father.left = rightChild;
		       else                      father.right= rightChild;}
		    else
		      root = rightChild;
		  }
	}


}
