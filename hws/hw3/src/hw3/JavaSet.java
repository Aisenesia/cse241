package hw3;

import java.util.Iterator;

//for var keyword i used java 11

/**
 * Set class that holds type of data as asked, it does not allow copies inside itself
 * @param <T> Type of element held in set
 */
public class JavaSet<T> implements JavaContainer<T>, Iterable<T> {
	private Object[] elements;
	private int size;

	/**
	 * Default constructor with a default capacity of 10.
	 */
	public JavaSet() {
		elements = new Object[10];// default capacity of 10
		size = 0;
	}

	/**
	 * Constructor with a specified capacity.
	 *
	 * @param capacity The initial capacity of the set.
	 */
	public JavaSet(int capacity) {
		elements = new Object[capacity];
		size = 0;
	}

	/**
	 * checks whether set has the element or not
	 * 
	 * @param element element to check
	 * @return True if set contains that element, False otherwise
	 */
	public boolean contains(T element) {
		for (var elems : this) {
			if (elems.equals(element))
				return true;
		}
		return false;
	}

	/**
	 * Adds an element to the set.
	 *
	 * @param element The element to be added.
	 * @throws IllegalArgumentException if an element with the same value is in the
	 *                                  set.
	 */
	public void add(T element) {
		if (contains(element))
			throw new IllegalArgumentException("Set already contains that element!");
		ensureCapacity();
		elements[size++] = element;
	}

	/**
	 * Removes an element from the set.
	 *
	 * @param element The element to be removed.
	 */
	public void remove(T element) {
		int deleteIndex = -1;
		for (int i = 0; i < size; i++) {
			if (elements[i].equals(element)) {
				deleteIndex = i;
				break;
			}
		}

		if (deleteIndex == -1)
			return; // not found

		for (int i = deleteIndex; i < size - 1; i++) {
			elements[i] = elements[i + 1];
		}

		elements[--size] = null;
	}

	/**
	 * Gets the size of the set.
	 *
	 * @return The size of the set.
	 */
	public int size() {
		return size;
	}

	/**
	 * Ensures the capacity of the set, increases if not enough
	 */
	private void ensureCapacity() {
		if (size == elements.length) {
			int newCapacity = elements.length * 2;
			Object[] newElements = new Object[newCapacity];
			for (int i = 0; i < size; i++) {
				newElements[i] = elements[i];
			}
			elements = newElements;
		}
	}

	/**
	 * Provides a string representation of the set.
	 *
	 * @return A string representation of the set.
	 */
	@Override
	public String toString() {

		if (size == 0) {
			return "set = {}, size = 0}";
		}

		String str = "set = {" + elements[0];
		for (int i = 1; i < size; i++) {
			str = str + ", " + elements[i];
		}
		str = str + "}, size = " + size + "}";

		return str;
	}

	/**
	 * Return the element at specified index
	 * 
	 * @param index Index of the element that will be returned.
	 * @return Element at given index.
	 * 
	 */
	@SuppressWarnings("unchecked")
	T getElement(int index) {
		if (index > size)
			throw new IndexOutOfBoundsException();
		return (T) elements[index];
	}

	/**
	 * Compares this JavaSet with another object for equality.
	 *
	 * @param o The object to compare with.
	 * @return True if the specified object is the same to this JavaSet by content,
	 *         false otherwise.
	 *
	 */
	@SuppressWarnings("unchecked")
	@Override
	public boolean equals(Object o) {
		if (this == o)
			return true;
		if (o == null || getClass() != o.getClass())
			return false;

		JavaSet<T> otherSet = (JavaSet<T>) o;
		if (size != otherSet.size())
			return false;
		for (var a : otherSet) {
			if (!otherSet.contains(a)) {
				return false;
			}
		}
		return true;
	}

	/**
	 * Creates an Iterator and returns that
	 * 
	 * @return Newly created iterator object
	 * 
	 */
	public Iterator<T> iterator() {
		// this is for Java ranged loops, getIterator function we asked to implement is
		// not a standard for Iterable interface.
		return new JavaSetIterator<T>();
	}

	/**
	 * Creates an Iterator an returns that
	 * 
	 * @return Newly created iterator object
	 */
	public Iterator<T> getIterator() {
		// this is for homework, Iterable interface uses iterator() function for ranged
		// loops.
		return new JavaSetIterator<T>();
	}

	/**
	 * Custom iterator class that implements Iterator from java.util
	 * 
	 * @param <T> Type of which object set holds
	 */
	@SuppressWarnings("hiding")
	public class JavaSetIterator<T> implements Iterator<T> {

		/**
		 * The current index of the iterator.
		 */
		private int currentIndex = 0;

		/**
		 * Checks if there is a next element in the iterator.
		 *
		 * @return True if there is a next element, false otherwise.
		 */
		public boolean hasNext() {
			return currentIndex < size;
		}

		/**
		 * Retrieves the next element in the iterator, advances index of the iterator
		 *
		 * @return The next element in the iterator, or null if there are no more
		 *         elements.
		 */
		@SuppressWarnings("unchecked")
		public T next() {
			if (hasNext()) {
				Object nextElement = elements[currentIndex++];
				return (T) nextElement;
			}
			return null;
		}

		public void remove() {
			throw new UnsupportedOperationException("Remove operation is not supported.");
		}

	}

}
